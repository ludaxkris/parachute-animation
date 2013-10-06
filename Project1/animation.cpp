////////////////////////////////////////
// animation.cpp
////////////////////////////////////////


#include "core.h"
#include "animation.h"
#include "channel.h"
#include "token.h"

void Animation::Load(const char *file) {
	Tokenizer token;
	char temp[256];
	token.Open(file);	

	token.FindToken("range");
	rangeMin = token.GetFloat();
	rangeMax = token.GetFloat();

	token.FindToken("numchannels");
	numChannels = token.GetFloat();

	while(1) {
		token.GetToken(temp);

		//Channels
		if(strcmp(temp,"channel") == 0) {
			Channel * chan = new Channel();

			chan->Load(token);
			channels.push_back(chan);
		}

		if(strcmp(temp,"}") == 0) {
			break;
		}
	}

	token.Close();
}

void Animation::Precompute() {
	for(int i=0; i<channels.size(); ++i) {
		channels.at(i)->precompute();
	}

}

void Animation::Evaluate(float time, Pose &p) {
	for(int i=0; i<channels.size(); ++i) {
		p.positions.push_back(channels.at(i)->evaluate(time));
	}
}