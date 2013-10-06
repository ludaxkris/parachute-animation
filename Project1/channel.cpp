////////////////////////////////////////
// channel.cpp
////////////////////////////////////////


#include "core.h"
#include "channel.h"


void Channel::Load(Tokenizer &token) {

	token.FindToken("{");

	//Extrapolate
	token.FindToken("extrapolate");
	token.GetToken(extraIn);
	token.GetToken(extraOut);

	//Keys
	token.FindToken("keys");
	numKeys = token.GetInt();
	token.FindToken("{");
	for(int i=0; i<numKeys; ++i) {
		Keyframe * frame = new Keyframe();
		frame->Load(token);
		keys.push_back(frame);
	}
	firstKey = keys.at(0);
	lastKey = keys.at(numKeys-1);

	token.FindToken("}");	//end keys
	token.FindToken("}");	//end channel
}

void Channel::precompute() {
	///Calculate tangents
	//loop through each key
	//check which tangent to use
	//if smooth, first and last use linear
	//store tangents as a,b,c,d (cubic coefficents)
	if(numKeys <= 1) {	//do nothing
		return;
	}

	for( int i=0; i<numKeys; ++i ) {
		Keyframe * key = keys.at(i);

		//Flat Tangents
		if(key->getRuleIn() == 0)
			key->tangentIn = 0;

		if(key->getRuleOut() == 0)
			key->tangentOut = 0;

		//Linear
		if(key->getRuleIn() == 1) {
			if( i == 0 ) {	//First in-tangent is undefined;
				key->tangentIn = 0;
			}
			else {
				float pos = key->value - keys.at(i-1)->value;
				float time = key->time - keys.at(i-1)->time;
				key->tangentIn = pos / time;
			}
		}

		if(key->getRuleOut() == 1) {
			if( i == numKeys-1 ) {	//Last out-tangent is undefined
				key->tangentOut = 0;
			}
			else {
				float pos = keys.at(i+1)->value - key->value;
				float time = keys.at(i+1)->time - key->time;
				key->tangentOut = pos / time;
			}
		}

		//Smooth
		if(key->getRuleIn() == 2) {
			if( i == numKeys-1 ) {		//perform linear
				float pos = key->value - keys.at(i-1)->value;
				float time = key->time - keys.at(i-1)->time;
				key->tangentIn = pos / time;
			}
			else if( i == 0 ) {		//First in-tangent is undefined;
				key->tangentIn = 0;
			}
			else {
				float pos = keys.at(i+1)->value - keys.at(i-1)->value;
				float time = keys.at(i+1)->time - keys.at(i-1)->time;
				key->tangentIn = pos / time;
			}
		}

		if(key->getRuleOut() == 2) {
			if( i == 0 ) {			//perform linear
				float pos = keys.at(i+1)->value - key->value;
				float time = keys.at(i+1)->time - key->time;
				key->tangentOut = pos / time;
			}
			else if( i == numKeys-1 ) {	//Last out-tangent is undefined
				key->tangentOut = 0;
			}
			else { 
				float pos = keys.at(i+1)->value - keys.at(i-1)->value;
				float time = keys.at(i+1)->time - keys.at(i-1)->time;
				key->tangentOut = pos / time;
			}
		}

		//Fixed
		if(key->getRuleIn() == 3) 
			key->tangentIn = (float) atof(key->ruleIn);

		if(key->getRuleOut() == 3) 
			key->tangentOut = (float) atof(key->ruleOut);
	}

	//Compute cubic coefficients from 1 to size-1
	for( int j=0; j<numKeys-1; ++j ) {
		Keyframe * key = keys.at(j);

		float time = keys.at(j+1)->time - key->time;
		float v0 = time * key->tangentOut;
		float v1 = time * keys.at(j+1)->tangentIn;

		key->timeDiff = 1 / time;
		
		key->cubicCoef(key->value, keys.at(j+1)->value, v0, v1);
	}

	//keys.at(numKeys)->cubicCoef(keys.at(numKeys)->value, 0, v0, 0);
}

//return position at time
float Channel::evaluate(float time) {

	if(numKeys == 0)	//no keys
		return 0;
	if(numKeys == 1)	//1 key
		return firstKey->value;

	//Out of current key range
	if(firstKey->time > time ) {	//time too small
		float cycles = (time - firstKey->time) / (lastKey->time - firstKey->time);
		cycles = fabs(cycles);	//make cycles non-negative
		int fullCycles = (int)cycles;
		float partialCycle = cycles - fullCycles;
		float offset;

		//determine extrapolation type
		switch(getExtraIn()) {
			case 0:					//constant
				return firstKey->value;
			case 1:					//linear
				//y = mx + b => v0(time-firstTime) + firstValue
				//tangentIn should be avoided
				return firstKey->tangentOut * (time - firstKey->time) + firstKey->value;
			case 2:					//cyclic
				return evaluate( firstKey->time + (partialCycle * (lastKey->time - firstKey->time)));
			case 3:					//cyclic_offset
				//end - beginning position
				offset = lastKey->value - firstKey->value;
				offset *= fullCycles;
				return offset + evaluate( firstKey->time + partialCycle );
			case 4:					//bounce
				//time flips on every odd cycle
				if(fullCycles % 2 == 0)	//even
					return evaluate( firstKey->time + partialCycle );
				else	//odd
					return evaluate( lastKey->time - (firstKey->time + partialCycle) );
		}
	}

	if(lastKey->time < time ) {	//time too large
		float cycles = (time - firstKey->time) / (lastKey->time - firstKey->time);
		int fullCycles = (int)cycles;
		float partialCycle = cycles - fullCycles;
		float offset;

		//determine extrapolation type
		switch(getExtraOut()) {
			case 0:					//constant
				return lastKey->value;
			case 1:					//linear
				//y = mx + b => v0(time-lastTime) + lastValue
				//tangentOut should be avoided
				return lastKey->tangentIn * (time - lastKey->time) + lastKey->value;
			case 2:					//cyclic
				return evaluate( firstKey->time + (partialCycle * (lastKey->time - firstKey->time)) );
			case 3:					//cyclic_offset
				//end - beginning position
				offset = lastKey->value - firstKey->value;
				offset *= fullCycles;
				return offset + evaluate( firstKey->time + partialCycle );
			case 4:					//bounce
				//time flips on every odd cycle
				if(fullCycles % 2 == 0)	//even
					return evaluate( firstKey->time + partialCycle );
				else	//odd
					return evaluate( firstKey->time + (lastKey->time - partialCycle) );
		}
	}

	//for(int i=0; i<numKeys; ++i) {
	//	Keyframe * key = keys.at(i);

	//	//if matches key
	//	if( fabs(key->time - time) < 0.0001 )
	//		return key->value;

	//	//check between span
	//	if( key->time < time && keys.at(i+1)->time > time ) {
	//		//calculate cubic span
	//		return key->evalCubic(time);
	//	}
	//}

	//return 0;
	//	

	//use Binary search to find key
	int i = 0;
	int j = keys.size()-1;
	int middle;
	Keyframe * key;
	while(i < j) {
		middle = (i+j) / 2;
		key = keys.at(middle);

		//if matches key
		if( fabs(key->time - time) < 0.001 )
			return key->value;

		//check between span
		if( key->time < time && keys.at(middle+1)->time > time ) {
			//calculate cubic span
			return key->evalCubic(time);
		}

		//look left
		if( key->time > time ) {
			j = middle;
			continue;
		}

		//look right
		else if( key->time < time ) {
			i = middle + 1;
			continue;
		}
	}
	return 0;
		

}

int Channel::getExtraIn() {
	//constant = 0
	//linear = 1;
	//cyclic = 2;
	//cyclic_offset = 3
	//bounce = 4
	if(strcmp(extraIn,"constant") == 0)
		return 0;
	else if(strcmp(extraIn,"linear") == 0)
		return 1;
	else if(strcmp(extraIn,"cycle") == 0)
		return 2;
	else if(strcmp(extraIn,"cycle_offset") == 0)
		return 3;
	else if(strcmp(extraIn,"bounce") == 0)
		return 4;
	else 
		return 0;
}

int Channel::getExtraOut() {
	//constant = 0
	//linear = 1;
	//cyclic = 2;
	//cyclic_offset = 3
	//bounce = 4
	if(strcmp(extraOut,"constant") == 0)
		return 0;
	else if(strcmp(extraOut,"linear") == 0)
		return 1;
	else if(strcmp(extraOut,"cycle") == 0)
		return 2;
	else if(strcmp(extraOut,"cycle_offset") == 0)
		return 3;
	else if(strcmp(extraOut,"bounce") == 0)
		return 4;
	else 
		return 0;
}