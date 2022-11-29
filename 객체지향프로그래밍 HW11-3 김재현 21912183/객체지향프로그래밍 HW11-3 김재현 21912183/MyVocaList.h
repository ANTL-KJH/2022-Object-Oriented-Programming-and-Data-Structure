/* MyVocaList.h */
#ifndef MY_VOCA_LIST_H
#define MY_VOCA_LIST_H
#include "MyVoca.h"
int NUM_MY_TOEIC_VOCA = 20;
MyVoca myToeicVocaList[] =
{
	MyVoca("personally", ADJ, { "individually", "privately", "directly" }, { "The president thanked him personally at the end of the ceremony." }),
	MyVoca("marginal", ADJ, { "insignificant", "minor", "samll" }, { "The improvement in her work performance was marginal." }),
	MyVoca("justly", ADJ, { "justifiably", "reasonably", "rightfully" }, { "The court case was justly tossed out before it could go to trial." }),
	MyVoca("initiate", VERB, { "start", "commence", "begin" }, { "It will take a few months before we can initiate the merger." }),
	MyVoca("forecast", VERB, { "predict", "foresee", "anticipate" }, { "The analyst forecasts a quick rise in stock prices for the next month. " }),
	MyVoca("announce", VERB, { "declare", "reveal", "disclose" }, { "They will announce the winner after all of the votes are counted." }),
	MyVoca("discontinue", NOUN, { "suspend", "cease", "halt" }, { "We discontinued the product because it was no longer profitable." }),
	MyVoca("attractive", ADJ, { "tempting", "alluring", "appealing" }, { "The clothing on the mannequin in the display window is attractive" }),
	MyVoca("critical", ADJ, { "significant", "vital", "crucial" }, { "An applicant's appearance is critical during a job interview." }),
	MyVoca("argue", VERB, { "claim", "dispute", "contend" }, { "The attorney argued that her opponent's statements were inaccurate." }),
	//10
	MyVoca("customize", VERB, { "tailor", "", "" }, { "You may customize your order by choosing the color and size." }),
	MyVoca("examin", VERB, { "go-through", "look-over", "" }, { "The woman is examining a document" }),
	MyVoca("clarity", NOUN, { "clearness", "", "" }, { "The buyer picked this mobile phone because of the clarity of the screen." }),
	MyVoca("eventually", ADJ, { "ultimately", "finally", "" }, { "Mr. Kramer eventually got over his fear of public speaking." }),
	MyVoca("promotion", NOUN, { "advertising", "marketing", "" }, { "The promotion of the new car model cost much more than planned." }),
	MyVoca("rating", NOUN, { "assessment", "evaluation", "" }, { "The new restaurant has received a five star rating." }),
	MyVoca("temporary", ADJ, { "impermanent", "transitory", "" }, { "The downturn in the city's economy is expected to be temporary." }),
	MyVoca("financial", ADJ, { "economic", "monetary", "" }, { "Some people prefer lasting fame to financial self-sufficiency" }),
	MyVoca("overtime", NOUN, { "additional-hours", "extra-hours", "" }, { "We have to work overtime because the office is understaffed." }),
	MyVoca("launch", VERB, { "release", "introduction", "" }, { "The firm advertised the new smartphone months before its launch." })
	//{ "-1", NOUN, { "" }, { "" } }, // end sentinel
};
#endif