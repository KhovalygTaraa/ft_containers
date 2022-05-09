/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:41:10 by swquinc           #+#    #+#             */
/*   Updated: 2021/08/10 15:41:11 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "map.hpp"
#include "../vector/vector.hpp"
#include <map>
#include <set>
#include <list>

//template<typename value>
//struct comporator: std::binary_function<value, value, bool> {
//	bool flag = false;
//	bool operator()(const value &first, const value &second) const {
//		if (flag == true)
//			std::cout << "haha" << std::endl;
//		return (first > second);
//	}
//};

void print(std::string str) {
	std::string boundary(6 + str.length(), '=');

	std::cout << "\e[1;92m" << boundary << "\e[0m" << std::endl;
	std::cout << "\e[1;92m==\e[0m\e[1;94m " << str << " \e[0m\e[1;92m==\e[0m" << std::endl;
	std::cout << "\e[1;92m" << boundary << "\e[0m" << std::endl;
}

std::string ftrue() {
	return ("\e[0;92mtrue\e[0m");
}

std::string ffalse() {
	return ("\e[0;91mfalse\e[0m");
}

#include <vector>
int main() {

	{
		ft::map<int, int> m;
		ft::map<int, int>::iterator it;

		m.insert(ft::make_pair(55, 55));
		m.insert(ft::make_pair(22, 22));
		m.insert(ft::make_pair(12, 12));
		m.insert(ft::make_pair(1, 1));
		m.insert(ft::make_pair(11, 11));
		m.insert(ft::make_pair(7, 7));
		m.insert(ft::make_pair(3, 3));
		m.insert(ft::make_pair(33, 33));
		m.insert(ft::make_pair(8, 8));
		m.insert(ft::make_pair(26, 26));
		m.insert(ft::make_pair(155, 155));
		m.insert(ft::make_pair(122, 122));
		m.insert(ft::make_pair(112, 112));
		m.insert(ft::make_pair(111, 111));
		m.insert(ft::make_pair(17, 17));
		m.insert(ft::make_pair(13, 13));
		m.insert(ft::make_pair(133, 133));
		m.insert(ft::make_pair(18, 18));
		m.insert(ft::make_pair(126, 126));

		print("insert");
		it = m.begin();

		while (it != m.end()) {
			std::cout << it->first << std::endl;
			it++;
		}

		print("find");
		std::cout << m.find(122)->second << std::endl;
		it = m.find(55);
		std::cout << it->second << std::endl;
		it++;
		std::cout << it->second << std::endl;
		it--;
		it--;
		std::cout << it->second << std::endl;

		print("count");

		std::cout << "1000 is exist? - " << (m.count(1000) ? ftrue() : ffalse()) << std::endl;
		std::cout << "1    is exist? - " << (m.count(1) ? ftrue() : ffalse()) << std::endl;
		std::cout << "0    is exist? - " << (m.count(0) ? ftrue() : ffalse()) << std::endl;
		std::cout << "155  is exist? - " << (m.count(155) ? ftrue() : ffalse()) << std::endl;
		std::cout << "26   is exist? - " << (m.count(26) ? ftrue() : ffalse()) << std::endl;

		print("equal_range");

		ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> er;

		er = m.equal_range(133);
		std::cout << er.first->first << std::endl;
		std::cout << er.second->first << std::endl;

		print("upper_bound");

		std::cout << m.upper_bound(133)->first << std::endl;
		std::cout << m.upper_bound(1)->first << std::endl;
		std::cout << m.upper_bound(2)->first << std::endl;

		print("lower_bound");

		std::cout << m.lower_bound(133)->first << std::endl;
		std::cout << m.lower_bound(1)->first << std::endl;
		std::cout << m.lower_bound(2)->first << std::endl;

		print("empty");

		std::cout << m.empty() << std::endl;

		print("clear");

		m.clear();
		it = m.begin();
		std::cout << m.empty() << std::endl;

		while (it != m.end()) {
			std::cout << it->first << std::endl;
			it++;
		}
		std::cout << std::endl;
		std::cout << "new test" << std::endl;

		{
			ft::map<int, int> m;
			ft::map<int, int>::iterator it;

			m.insert(ft::make_pair(55, 55));
			m.insert(ft::make_pair(22, 22));
			m.insert(ft::make_pair(12, 12));
			m.insert(ft::make_pair(1, 1));
			m.insert(ft::make_pair(11, 11));
			m.insert(ft::make_pair(7, 7));
			m.insert(ft::make_pair(3, 3));
			m.insert(ft::make_pair(33, 33));

			print("erase testing");
			print("before erase");
			it = m.begin();

			while (it != m.end()) {
				std::cout << it->first << std::endl;
				it++;
			}

			print("after erase");

			m.erase(m.begin());
			m.erase(--m.end());

			it = m.begin();

			while (it != m.end()) {
				std::cout << it->first << std::endl;
				it++;
			}
			print("size");

			std::cout << m.size() << std::endl;
			m.insert(ft::make_pair(323, 33));
			std::cout << m.size() << std::endl;
			m.erase(12);
			std::cout << m.size() << std::endl;

			print("full erase");

			m.erase(m.begin(), m.end());
			it = m.begin();

			while (it != m.end()) {
				std::cout << it->first << std::endl;
				it++;
			}
		}


		std::cout << std::endl;
		std::cout << "new test" << std::endl;
		{
			ft::map<int, int> m;
			ft::map<int, int>::iterator it;

			m.insert(ft::make_pair(55, 55));
			m.insert(ft::make_pair(22, 22));
			m.insert(ft::make_pair(12, 12));
			m.insert(ft::make_pair(1, 1));
			m.insert(ft::make_pair(11, 11));
			m.insert(ft::make_pair(7, 7));
			m.insert(ft::make_pair(3, 3));
			m.insert(ft::make_pair(33, 33));

		}
	}

}
