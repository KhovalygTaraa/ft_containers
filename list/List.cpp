/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:24:45 by swquinc           #+#    #+#             */
/*   Updated: 2021/04/30 21:44:43 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "List.hpp"
#include <list>
#include <stack>
#include <iostream>
#include <vector>

//int main()
//{
////	ft::list<int> a;
//	std::list<int> b;
//
////
////	a.push_back(42);
////	a.push_back(21);
////	a.push_back(100);
//	b.push_back(42);
//	b.push_back(21);
//	b.push_back(100);
//
//	std::list<int>::iterator it;
//
//	it = b.begin();
//	it--;
//	it--;
//	std::cout << *it  << std::endl;
////	std::cout << *a.end() << std::endl;
//
//	return 0;
//}

int main()
{
	std::cout << "\e[1;36m/************************ Constructors ************************/\e[0m" << std::endl;
	/******************************************************************************************************/
	/******************************************************************************************************/
	/******************************************** Constructors ********************************************/
	/******************************************************************************************************/
	/******************************************************************************************************/

	std::cout << "\n\e[1;33m/**** Default constructor ****/\e[0m" << std::endl;
	/*********************************************************************/
	/*********************************************************************/
	/************************ Default constructor ************************/
	/*********************************************************************/
	/*********************************************************************/
	ft::list<int> m1;
	std::list<int> r1;

	/**************/
	/*** size() ***/
	/**************/
	std::cout << "\e[1;32m ft: "<< m1.size() << "\e[0m";
	if (r1.size() == m1.size())
		std::cout << "\e[1;32m | std: " << r1.size() << "\e[0m - size()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << r1.size() << "\e[0m - size()"<< std::endl;

	/***************/
	/*** begin() ***/
	/***************/
	std::cout << "\e[1;32m ft: "<< *m1.begin() << "\e[0m";
	if (*r1.begin() == *m1.begin())
		std::cout << "\e[1;32m | std: " << *r1.begin() << "\e[0m - begin()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << *r1.begin() << "\e[0m - begin()"<< std::endl;

	/*************/
	/*** end() ***/
	/*************/
	std::cout << "\e[1;32m ft: "<< *m1.end() << "\e[0m";
	if (*r1.end() == *m1.end())
		std::cout << "\e[1;32m | std: " << *r1.end() << "\e[0m - end()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << *r1.end() << "\e[0m - end()"<< std::endl;

	/***************/
	/*** front() ***/
	/***************/
	std::cout << "\e[1;32m ft: "<< m1.front() << "\e[0m";
	if (r1.front() == m1.front())
		std::cout << "\e[1;32m | std: " << r1.front() << "\e[0m - front()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << r1.front() << "\e[0m - front()"<< std::endl;

	/**************/
	/*** back() ***/
	/**************/
	std::cout << "\e[1;32m ft: "<< m1.back() << "\e[0m";
	if (r1.back() == m1.back())
		std::cout << "\e[1;32m | std: " << r1.back() << "\e[0m - back()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << r1.back() << "\e[0m - back()"<< std::endl;

	/***************/
	/*** empty() ***/
	/***************/
	std::cout << "\e[1;32m ft: "<< m1.empty() << "\e[0m";
	if (r1.empty() == m1.empty())
		std::cout << "\e[1;32m | std: " << r1.empty() << "\e[0m - empty()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << r1.empty() << "\e[0m - empty()"<< std::endl;

	/******************************************/
	/*** check_iterator && elements of list ***/
	/******************************************/
	std::cout << "\e[1;35m ADD: check_iterator && elements of list\e[0m" << std::endl;
	ft::list<int>::iterator itm1;
	std::list<int>::iterator itr1;

	itm1 = m1.begin();
	itr1 = r1.begin();
	for (int i = 0; i != 1; i++)
	{
		if (*itm1 == *itr1)
			std::cout << "\e[1;35m " << i << ") \e[0m" << "\e[1;32m ft: " << *itm1 << " | std: " << *itr1 << "\e[0m" << std::endl;
		else
			std::cout << "\e[1;35m " << i << ") \e[0m" << "\e[1;31m ft: " << *itm1 << " | std: " << *itr1 << "\e[0m" << std::endl;
		itm1++;
		itr1++;
	}

	std::cout << "\n\e[1;33m/**** Fill constructor ****/\e[0m" << std::endl;

	/********************************************************************************/
	/********************************************************************************/
	/******************************* Fill constructor *******************************/
	/********************************************************************************/
	/********************************************************************************/

	ft::list<int> m2(5);
	std::list<int> r2(5);

	/**************/
	/*** size() ***/
	/**************/
	std::cout << "\e[1;32m ft: "<< m2.size() << "\e[0m";
	if (r2.size() == m2.size())
		std::cout << "\e[1;32m | std: " << r2.size() << "\e[0m - size()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << r2.size() << "\e[0m - size()"<< std::endl;

	/***************/
	/*** begin() ***/
	/***************/
	std::cout << "\e[1;32m ft: "<< *m2.begin() << "\e[0m";

	if (*r2.begin() == *m2.begin())
		std::cout << "\e[1;32m | std: " << *r2.begin() << "\e[0m - begin()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << *r2.begin() << "\e[0m - begin()"<< std::endl;

	/*************/
	/*** end() ***/
	/*************/

	std::cout << "\e[1;32m ft: "<< *m2.end() << "\e[0m";
	if (*r2.end() == *m2.end())
		std::cout << "\e[1;32m | std: " << *r2.end() << "\e[0m - end()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << *r2.end() << "\e[0m - end()"<< std::endl;

	/***************/
	/*** front() ***/
	/***************/
	std::cout << "\e[1;32m ft: "<< m2.front() << "\e[0m";
	if (r2.front() == m2.front())
		std::cout << "\e[1;32m | std: " << r2.front() << "\e[0m - front()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << r2.front() << "\e[0m - front()"<< std::endl;

	/**************/
	/*** back() ***/
	/**************/
	std::cout << "\e[1;32m ft: "<< m2.back() << "\e[0m";
	if (r2.back() == m2.back())
		std::cout << "\e[1;32m | std: " << r2.back() << "\e[0m - back()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << r2.back() << "\e[0m - back()"<< std::endl;

	/***************/
	/*** empty() ***/
	/***************/
	std::cout << "\e[1;32m ft: "<< m2.empty() << "\e[0m";
	if (r2.empty() == m2.empty())
		std::cout << "\e[1;32m | std: " << r2.empty() << "\e[0m - empty()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << r2.empty() << "\e[0m - empty()"<< std::endl;

	/******************************************/
	/*** check_iterator && elements of list ***/
	/******************************************/
	std::cout << "\e[1;35m ADD: check_iterator && elements of list\e[0m" << std::endl;
	ft::list<int>::iterator itm2;
	std::list<int>::iterator itr2;

	itm2 = m2.begin();
	itr2 = r2.begin();
	for (int i = 0; i != 6; i++)
	{
		if (*itm2 == *itr2)
			std::cout << "\e[1;35m " << i << ") \e[0m" << "\e[1;32m ft: " << *itm2 << " | std: " << *itr2 << "\e[0m" << std::endl;
		else
			std::cout << "\e[1;35m " << i << ") \e[0m" << "\e[1;31m ft: " << *itm2 << " | std: " << *itr2 << "\e[0m" << std::endl;
		itm2++;
		itr2++;
	}
	std::cout << "\n\e[1;33m/**** Copy constructor ****/\e[0m" << std::endl;

	/********************************************************************************/
	/********************************************************************************/
	/******************************* Copy constructor *******************************/
	/********************************************************************************/
	/********************************************************************************/
	ft::list<int> m3(m2);
	std::list<int> r3(r2);

	/**************/
	/*** size() ***/
	/**************/
	std::cout << "\e[1;32m ft: "<< m3.size() << "\e[0m";
	if (r3.size() == m3.size())
		std::cout << "\e[1;32m | std: " << r3.size() << "\e[0m - size()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << r3.size() << "\e[0m - size()"<< std::endl;

	/***************/
	/*** begin() ***/
	/***************/
	std::cout << "\e[1;32m ft: "<< *m3.begin() << "\e[0m";
	if (*r3.begin() == *m3.begin())
		std::cout << "\e[1;32m | std: " << *r3.begin() << "\e[0m - begin()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << *r3.begin() << "\e[0m - begin()"<< std::endl;

	/*************/
	/*** end() ***/
	/*************/
	std::cout << "\e[1;32m ft: "<< *m3.end() << "\e[0m";
	if (*r3.end() == *m3.end())
		std::cout << "\e[1;32m | std: " << *r3.end() << "\e[0m - end()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << *r3.end() << "\e[0m - end()"<< std::endl;

	/***************/
	/*** front() ***/
	/***************/
	std::cout << "\e[1;32m ft: "<< m3.front() << "\e[0m";
	if (r3.front() == m3.front())
		std::cout << "\e[1;32m | std: " << r3.front() << "\e[0m - front()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << r3.front() << "\e[0m - front()"<< std::endl;

	/**************/
	/*** back() ***/
	/**************/
	std::cout << "\e[1;32m ft: "<< m3.back() << "\e[0m";
	if (r3.back() == m3.back())
		std::cout << "\e[1;32m | std: " << r3.back() << "\e[0m - back()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << r3.back() << "\e[0m - back()"<< std::endl;

	/***************/
	/*** empty() ***/
	/***************/
	std::cout << "\e[1;32m ft: "<< m3.empty() << "\e[0m";
	if (r3.empty() == m3.empty())
		std::cout << "\e[1;32m | std: " << r3.empty() << "\e[0m - empty()"<< std::endl;
	else
		std::cout << "\e[1;31m | std: " << r3.empty() << "\e[0m - empty()"<< std::endl;

	/******************************************/
	/*** check_iterator && elements of list ***/
	/******************************************/
	std::cout << "\e[1;35m ADD: check_iterator && elements of list\e[0m" << std::endl;
	ft::list<int>::iterator itm3;
	std::list<int>::iterator itr3;

	itm3 = m3.begin();
	itr3 = r3.begin();
	for (int i = 0; i != 6; i++)
	{
		if (*itm3 == *itr3)
			std::cout << "\e[1;35m " << i << ") \e[0m" << "\e[1;32m ft: " << *itm3 << " | std: " << *itr3 << "\e[0m" << std::endl;
		else
			std::cout << "\e[1;35m " << i << ") \e[0m" << "\e[1;31mft: " << *itm3 << " | std: " << *itr3 << "\e[0m" << std::endl;
		itm3++;
		itr3++;
	}

	std::cout << "\n\e[1;33m/**** Range constructor ****/\e[0m" << std::endl;

	/*********************************************************************************/
	/*********************************************************************************/
	/******************************* Range constructor *******************************/
	/*********************************************************************************/
	/*********************************************************************************/
	ft::list<int> m4(m3.begin(), m3.end());
	std::list<int> r4(r3.begin(), r3.end());

	/**************/
	/*** size() ***/
	/**************/
	std::cout << "\e[1;32m ft: "<< m4.size() << "\e[0m";
	if (r3.size() == m4.size())
		std::cout << "\e[1;32m | std: " << r3.size() << "\e[0m - size()" << std::endl;
	else
		std::cout << "\e[1;31m | std: " << r3.size() << "\e[0m - size()" << std::endl;

	/***************/
	/*** begin() ***/
	/***************/
	std::cout << "\e[1;32m ft: "<< *m4.begin() << "\e[0m";
	if (*r3.begin() == *m4.begin())
		std::cout << "\e[1;32m | std: " << *r3.begin() << "\e[0m - begin()" << std::endl;
	else
		std::cout << "\e[1;31m | std: " << *r3.begin() << "\e[0m - begin()" << std::endl;

	/*************/
	/*** end() ***/
	/*************/
	std::cout << "\e[1;32m ft: "<< *m4.end() << "\e[0m";
	if (*r3.end() == *m4.end())
		std::cout << "\e[1;32m | std: " << *r3.end() << "\e[0m - end()" << std::endl;
	else
		std::cout << "\e[1;31m | std: " << *r3.end() << "\e[0m - end()" << std::endl;

	/***************/
	/*** front() ***/
	/***************/
	std::cout << "\e[1;32m ft: "<< m4.front() << "\e[0m";
	if (r3.front() == m4.front())
		std::cout << "\e[1;32m | std: " << r3.front() << "\e[0m - front()" << std::endl;
	else
		std::cout << "\e[1;31m | std: " << r3.front() << "\e[0m - front()" << std::endl;

	/**************/
	/*** back() ***/
	/**************/
	std::cout << "\e[1;32m ft: "<< m4.back() << "\e[0m";
	if (r3.back() == m4.back())
		std::cout << "\e[1;32m | std: " << r3.back() << "\e[0m - back()" << std::endl;
	else
		std::cout << "\e[1;31m | std: " << r3.back() << "\e[0m - back()" << std::endl;

	/***************/
	/*** empty() ***/
	/***************/
	std::cout << "\e[1;32m ft: "<< m4.empty() << "\e[0m";
	if (r3.empty() == m4.empty())
		std::cout << "\e[1;32m | std: " << r3.empty() << "\e[0m - empty()" << std::endl;
	else
		std::cout << "\e[1;31m | std: " << r3.empty() << "\e[0m - empty()" << std::endl;

	/******************************************/
	/*** check_iterator && elements of list ***/
	/******************************************/
	std::cout << "\e[1;35m ADD: check_iterator && elements of list\e[0m" << std::endl;
	ft::list<int>::iterator itm4;
	std::list<int>::iterator itr4;

	itm4 = m2.begin();
	itr4 = r2.begin();
	for (int i = 0; i != 6; i++)
	{
		if (*itm4 == *itr4)
			std::cout << "\e[1;35m " << i << ") \e[0m" << "\e[1;32m ft: " << *itm4 << " | std: " << *itr4 << "\e[0m" << std::endl;
		else
			std::cout << "\e[1;35m " << i << ") \e[0m" << "\e[1;31m ft: " << *itm4 << " | std: " << *itr4 << "\e[0m" << std::endl;
		itm4++;
		itr4++;
	}

    return (0);
}

