/*
efficient n-way merge assuming pre-sorted records as discussed during interview.
I may not be good at interviews; but problem solving yes.
I really did not like the way we implemented the N-way-Merge during the interview.
too much trashing(construct-destruction) occuring in the process (unecessary clock cycles) along with recursion overhead.
I only go the recursion route if I absolutely have to.

so to clear my name/label/brand/reputation here is what poped into my mind on Monday april 10th 2017 morning; and I must
say, without going to google or any other online source; but I must admit using an IDE ==> VS community 2017.
by the way, U shouldn't be able to find any thing similar online; well I hope so.
*/
#include <iostream>
#include <vector>
#include <memory>



typedef struct _recommendation {
	int score = INT_MIN;
	char * notes = nullptr;

	_recommendation(int value): score(value) {

	}
} recommendation;

typedef std::vector<std::shared_ptr<recommendation>> shared_recommendations;

std::shared_ptr<recommendation> * multiway_merge(std::vector<shared_recommendations> lists, size_t &newlist_size) {

	size_t total_length = 0;
	
	for (shared_recommendations& list : lists) {
		if (list.size() > 0)
		{
			total_length += list.size();
		}			
	}

	std::shared_ptr<recommendation>* sorted_result = new std::shared_ptr<recommendation>[total_length];
	newlist_size = total_length;

	memset(sorted_result, NULL, sizeof sorted_result);
	size_t global_idx = total_length;

	for (auto& rec_list : lists)
	{
		size_t i = 0;
		size_t rec_size = rec_list.size();
		
		size_t global_start_idx = global_idx;
		global_idx = global_idx - rec_size ;

		for (size_t k = global_idx; k < total_length; k++)
		{
			if (i >= rec_size)
			{
				//the list should already be well sorted
				break;
			}
			else if (global_start_idx >= total_length)
			{
				//append remaining items in current recommendations to the list
				while (i < rec_size)
				{
					sorted_result[k] = rec_list[i];
					++k;
					++i;
				}
				break;
			}
			else
			{
				if (sorted_result[global_start_idx]->score > rec_list[i]->score)
				{
					sorted_result[k] = sorted_result[global_start_idx];
					++global_start_idx;
				}
				else
				{
					sorted_result[k] = rec_list[i];
					++i;
				}
			}
		}
	}
	return sorted_result;
}

int main()
{
	std::vector<std::shared_ptr<recommendation>> list1 = {
		std::make_shared<recommendation>(100), 
		std::make_shared<recommendation>(89), 
		std::make_shared<recommendation>(15), 
		std::make_shared<recommendation>(68), 
		std::make_shared<recommendation>(23), 
		std::make_shared<recommendation>(15), 
		std::make_shared<recommendation>(6), 
		std::make_shared<recommendation>(5)
	};

	std::vector<std::shared_ptr<recommendation>> list2 = {
		std::make_shared<recommendation>(92),
		std::make_shared<recommendation>(86),
		std::make_shared<recommendation>(85),
		std::make_shared<recommendation>(84),
		std::make_shared<recommendation>(77),
		std::make_shared<recommendation>(71),
		std::make_shared<recommendation>(63),
		std::make_shared<recommendation>(56),
		std::make_shared<recommendation>(47),
		std::make_shared<recommendation>(27),
		std::make_shared<recommendation>(9),
		std::make_shared<recommendation>(3),
		std::make_shared<recommendation>(1)
	};
	std::vector<std::shared_ptr<recommendation>> list3 = {
		std::make_shared<recommendation>(97),
		std::make_shared<recommendation>(89),
		std::make_shared<recommendation>(86),
		std::make_shared<recommendation>(80),
		std::make_shared<recommendation>(63),
		std::make_shared<recommendation>(55),
		std::make_shared<recommendation>(47),
		std::make_shared<recommendation>(43)
	};

	shared_recommendations list4;

	std::vector<shared_recommendations> recs = { list1, list2, list3, list4 };

	size_t newlist_size = 0;
	std::shared_ptr<recommendation> * sortedresult =  multiway_merge(std::move(recs), newlist_size);
	size_t count_idx = 0;

	while(sortedresult != '\0')
	{
		count_idx += 1;
		std::cout << count_idx << ")\t" << (*sortedresult)->score << std::endl;
		sortedresult++;
		if (count_idx >= newlist_size)
			break;
	}

	std::cin.get();
	return 0;
}