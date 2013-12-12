/** \file TemplatedPermutation.h
*
* \details This file contains some facilities to calculate
*		   all permutations of given set of elements
*
*  \author Wesley Mesquita
*  \date   2013
*/

#include<iostream>
#include<string>
#include<vector>
#include<memory>

template<typename T>
class PermutationGenerator{

public:

	PermutationGenerator(const std::vector<T>& new_elems) :
		elems(new_elems)
	{
		indexes.clear();
	}

	/** \function  void permutation(const std::vector<T>& elems,
	const size_t ini,
	std::vector<std::vector<int>>& perms);

	* \brief main function to be used: just pass a vector of objects to be
	permuted
	*
	*/
	void doPermutations(){

		std::vector<elem_pos<T>> elems_track;

		for (int i = 0; i < (int)elems.size(); i++){
			elems_track.push_back({ i, std::shared_ptr<T>(new T(elems.at(i))) });
		}

		permutation_tracked(elems_track, 0, indexes);
	}
	
	/** \fn void printPerm(const std::vector<T>& elems,
	*	const std::vector<std::vector<int>>& index)
	*   \brief print all permutations of a vector of elements
	*   \param elems original elements vector
	*	\param index vector of vectos containing all permutations of elems
	*
	*	\warning complex objects MUST implement the operator << 
	*/
	void printPermutations()
	{
		for (std::vector<int> vec : indexes){
			std::cout << "|";
			for (size_t i : vec){
				std::cout << elems[i];
			}
			std::cout << "|" << std::endl;
		}
	}

private:
	/** \class elem_pos
	*  \brief container for permutation elements. It should track
	*		  the element position. When you see 'tracked', this is the reason:
	*		  keep a list of integers is (genaraly) cheaper than keep objects
	*/
	template<typename T>
	class elem_pos{
	public:
		elem_pos(int _pos, std::shared_ptr<T> t) :
			pos(_pos),
			T_ptr(t)
		{};

		int pos;
		std::shared_ptr<T> T_ptr;
	};

	/** \function std::vector<int> getSequence(const std::vector< elem_pos<T> >& vec)
	* \brief  Given a vector of elem_pos<T>, extract the
	*		 positions of these elements and return it.
	* \warning This function returns with std::move
	*/
	std::vector<int> getSequence(const std::vector< elem_pos<T> >& vec){
		std::vector<int> seq;
		seq.reserve(vec.size());
		for (elem_pos<T> elem : vec){
			seq.push_back(elem.pos);
		}
		return std::move(seq);
	}

	/** \function void permutation_tracked(std::vector< elem_pos<T> >& elems_tracked,
	*	const size_t ini,
	*	std::vector<std::vector<int>>& perms)
	*
	*   \brief helper function to the permutation process.
	*	\param elems_tracked vector of tracked elements for permutation
	*	\param ini where to start permutation
	*	\param perms a reference to a vector of vectors containing all permutations
	*/
	void permutation_tracked(std::vector< elem_pos<T> >& elems_tracked,
		const size_t ini,
		std::vector<std::vector<int>>& perms){

		// the base case of recursion happens when the pivot
		// is already the final element
		for (int i = ini; i < elems_tracked.size(); i++){

			// i is the permutations pivot. The logic is to
			// keep elems_tracked[i] | i < ini untouched and 
			// permute items for i>ini. As we always copy the entire
			// vector we will get permutation in sub-vectors 
			// but have always all the sequence
			std::vector< elem_pos<T> > elems_tracked_copy;
			elems_tracked_copy.reserve(elems_tracked.size());

			for (auto elem : elems_tracked){
				elems_tracked_copy.push_back(elem);
			}

			permutation_tracked(elems_tracked_copy, ini + 1, perms);

			if (i != ini){
				std::swap(elems_tracked[ini], elems_tracked[i]);
			}
			else{
				std::swap(elems_tracked[ini], elems_tracked[elems_tracked.size() - 1]);
			}
		}

		// Store just the sequence the indexes
		if (ini == elems_tracked.size()){
			perms.push_back(getSequence(elems_tracked));
		}
	}


	const std::vector<T>& elems;
	std::vector<std::vector<int>> indexes;
};
