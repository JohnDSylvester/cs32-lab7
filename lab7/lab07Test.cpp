#include "tddFuncs.cpp"
#include "WordCount.cpp"
#include <sstream>

int main(){
	WordCount tester;

	//testing make Valid Word
	assertEquals("pizza", tester.makeValidWord("Pizza"), "makeValidWord will make everything lowercase", __LINE__);
	assertEquals("pizza", tester.makeValidWord(".;]pi!!zz^&a234"), "makeValidWord will remove all numbers and special characters", __LINE__);
	assertEquals("let's", tester.makeValidWord("l!^#@et's"), "makeValidWord will remove special characters besides \'", __LINE__);\
	assertEquals("let-us", tester.makeValidWord("----let-us----"), "makeValidWord will remove special characters besides a singular -", __LINE__);


	//testing Increment which by proxy will test all getters
	tester.incrWordCount("Pizza");
	assertEquals(1, tester.getWordCount("pizza"), "incrWordCount adds pizza to the hash table", __LINE__);
	assertEquals(1, tester.getNumUniqueWords(), "getNumUniqueWords finds one word(pizza)", __LINE__);
	assertEquals(1, tester.getTotalWords(), "getTotalWords finds one word (pizza)", __LINE__);
	tester.incrWordCount("Pizza");
        assertEquals(2, tester.getWordCount("pizza"), "incrWordCount increments pizza", __LINE__);
	assertEquals(1, tester.getNumUniqueWords(), "getNumUniqueWords finds one word(pizza)", __LINE__);
	assertEquals(2, tester.getTotalWords(), "getTotalWords finds two words (2 pizzas)", __LINE__);
	tester.incrWordCount("cheese");
	assertEquals(1, tester.getWordCount("cheese"), "incrWordCount adds cheese to the hash table", __LINE__);
        assertEquals(2, tester.getNumUniqueWords(), "getNumUniqueWords finds two words(pizza and cheese)", __LINE__);
        assertEquals(3, tester.getTotalWords(), "getTotalWords finds 3 words (2 pizzas and 1 cheese)", __LINE__);
	
	//testing Decrement 
	tester.decrWordCount("pizza");
	assertEquals(1, tester.getWordCount("pizza"), "decrWordCount makes pizza\'s count 1", __LINE__);
        assertEquals(2, tester.getNumUniqueWords(), "getNumUniqueWords finds two words(pizza and cheese)", __LINE__);
        assertEquals(2, tester.getTotalWords(), "getTotalWords finds two word (1 pizza and 1 cheese)", __LINE__);
	tester.decrWordCount("pizza");
	assertEquals(0, tester.getWordCount("pizza"), "decrWordCount makes pizza\'s count0 and deletes it", __LINE__);
        assertEquals(1, tester.getNumUniqueWords(), "getNumUniqueWords finds one word(cheese)", __LINE__);
        assertEquals(1, tester.getTotalWords(), "getTotalWords finds one word (cheese)", __LINE__);

	//decrement something not in our hash
	assertEquals(-1, tester.decrWordCount("pizza"), "decrWordCount can't decrement something not in the hash and returns -1", __LINE__);	

	tester.decrWordCount("cheese");
	std::ostringstream oss;
	 tester.incrWordCount("Pizza");
	 tester.addAllWords("Pizza Pasta \t Put it \n in a box");

	 assertEquals(7, tester.getNumUniqueWords(), "getNumUniqueWords finds seven words", __LINE__);
	 assertEquals(2, tester.getWordCount("pizza"), "pizza count should be 2", __LINE__);
	 tester.dumpWordsSortedByWord(oss);
	 std::string results = oss.str();
	 std::string expected = "put,1\npizza,2\npasta,1\nit,1\nin,1\nbox,1\na,1\n";
	 assertEquals(expected, results, "dump sorted by word", __LINE__);
	 std::ostringstream oss2;
	 tester.dumpWordsSortedByOccurence(oss2);
	 results = oss2.str();
	 expected = "pizza,2\na,1\nbox,1\nin,1\nit,1\npasta,1\nput,1\n";
	 assertEquals(expected, results, "dump sorted by word", __LINE__);
	 
}
