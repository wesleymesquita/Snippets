/** \file TemplatedPermutations.cpp
*	\brief Tests for class PermutationGenerator
*
*/

#include "PermutationGenerator.hpp"

/*! \fn int perm_str(std::string& str, int ini)  
* \brief prints in stdout all permutations of a given string
* \param str a std::string containing characters to be permutated
* \param ini an int where to start permutation (for str[i]| i< ini)
*					will be fixed
*
*/
int perm_str(std::string& str, int ini) {
	for (size_t i = ini; i < str.size(); i++){
		std::string str_copy = str;
		perm_str(str_copy, ini + 1);
		std::swap(str[ini], str[i + 1]);
	}
	if (ini == str.size()){
		std::cout << str << std::endl;
	}
}

class BidOrder{
public:
	BidOrder(const std::string& _stock_ticker,
		double _bid,
		const std::string& _operator_id) :
		stock_ticker(_stock_ticker),
		bid(_bid),
		operator_id(_operator_id) { };

	friend std::ostream& operator<<(std::ostream& os, const BidOrder& bo){
		os << "| " << bo.stock_ticker << "|"
			<< bo.bid << "|" << bo.operator_id << "|";
		return os;
	}

private:
	std::string stock_ticker;
	double bid;
	std::string operator_id;
};

int main(){
	// Algo check
	std::string str = "ABCDEF";
	perm_str(str, 0);
	
	// char
	std::vector<char> vecChar = { 'A', 'B', 'C' };
	PermutationGenerator<char> permChar(vecChar);
	permChar.doPermutations();
	permChar.printPermutations();

	//int
	std::vector<int> vecInt = { 1, 1, 3, 4, 5 };
	PermutationGenerator<int> permInt(vecInt);
	permInt.doPermutations();
	permInt.printPermutations();
	
	//complex obj
	std::vector<BidOrder> vecBidOrder
		= { { "PETR3", 20.01, "ID19284" },
		{ "PETR4", 21.03, "ID56346" },
		{ "VALE5", 30.04, "ID56346" },
		{ "VALE5", 30.03, "ID43424" } };
	PermutationGenerator<BidOrder> permBidOrder(vecBidOrder);
	permBidOrder.doPermutations();
	permBidOrder.printPermutations();

	return 0;
}
