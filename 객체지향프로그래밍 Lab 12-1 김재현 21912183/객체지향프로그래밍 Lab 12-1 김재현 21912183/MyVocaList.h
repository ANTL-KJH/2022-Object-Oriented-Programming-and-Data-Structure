/*MyVocaList.h*/
#ifndef MY_VOCA_LIST_H
#define MY_VOCA_LIST_H
#include "MyVoca.h"

int NUM_MY_TOEIC_VOCA = 13;
MyVoca myToeicVocaList[] =
{
	MyVoca("mean", NOUN, { "average", "norm", "median", "middle", "midpoint", "(ant) extremity" },{ "the mean error", "the golden mean", "the arithmetical mean", "the geometric mean" }),
	MyVoca("mean", ADJ, { "nasty", "poor", "middle", "miserly", "paltry" }, { "a man of mean intelligence", "a mean appearance" }),		// repetition
	MyVoca("panel", NOUN, { "jury", "judge", "committee" }, { "A panel selected which of the candidates to put on the short list." }),
	MyVoca("warehouse", NOUN, { "storage", "store", "stockroom" }, { "More products will be delivered from the warehouse on Saturday." }),
	MyVoca("awareness", NOUN, { "perception", "attention", "" }, { "The mayor wants to raise awareness about violence in the city." }),
	MyVoca("foster", ADJ, { "substitute", "adoptive", "stand-in" }, { "" }),
	MyVoca("imperative", ADJ, { "authoritative", "vital" }, { "" }),
	MyVoca("imperative", NOUN, { "necessity", "essential", "requirement" }, { "" }),	// repetition
	MyVoca("contract", VERB, { "agree", "pledge", "undertake" }, { "" }),
	MyVoca("admiring", ADJ, { "appreciative", "", "" }, { "As the model walked across the stage, he drew many admiring glances" }),
	//10
	MyVoca("retail", NOUN, { "market", "stock" }, { "Consumers buy goods at the store, shops buy goods at the retail, and retailers buy goods at the wholesaler." }),
	MyVoca("consolidate", ADJ, { "combined", "united" }, { "Various opinions are important when doing homework with the same group in school or club, but consolidated opinions are important at the end." }),
	MyVoca("statement", NOUN, { "declaration", "", "" }, { "He rephrased his statement in order to get his point across clearer" }),
	MyVoca("announce", VERB, { "declare", "reveal", "disclose" }, { "They will announce the winner after all of the votes are counted." }),
	MyVoca("crowded", ADJ, { "congested", "busy", "jammed" }, { "The department store is crowded today because it is a Saturday" }),
	MyVoca("common", ADJ, { "usual", "standard", "familiar" }, { "When you use a common object, you shouldn't just use it recklessly, but you should save it like your own." }),
	MyVoca("endless", ADJ, { "ceaseless", "infinite", "" }, { "The student provided an endless list of excuses for not completing his work." }),
	MyVoca("consent", NOUN, { "agree", "concur", "assent" }, { "When others argue their opinions, they should think deeply and express their opinions, not unconditionally consent." }),
	MyVoca("fiction", NOUN, { "novel", "tale", "story" }, { "The bookstore carries mostly works of popular fiction." }),
	MyVoca("assumption", NOUN, { "presumption", "guess", "" }, { "We invested on the assumption that the stock was profitable." }),
	//{ "-1", NOUN, { "" }, { "" } }, // end sentinel
};

#endif