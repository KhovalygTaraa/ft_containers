/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:47:41 by swquinc           #+#    #+#             */
/*   Updated: 2021/08/14 19:47:41 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include "../vector/vector.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <set>

int main() {
	ft::vector<int> ha;
	ha.push_back(22);
	ft::stack<int, ft::vector<int> > test(ha);
	ft::stack<int, ft::vector<int> > test2(ha);

	test2.push(42);
	test.push(42);

	std::cout << test.top() << std::endl;
	std::cout << test2.top() << std::endl;

	test.pop();
	test2.pop();

	std::cout << test.top() << std::endl;
	std::cout << test2.top() << std::endl;

	test.push(42);
	test2.push(42);
	test.push(42);
	test2.push(42);
	test.push(42);
	test2.push(42);
	test.push(42);
	test2.push(42);

	std::cout << test.size() << std::endl;
	std::cout << test2.size() << std::endl;

	std::cout << (test == test2) << std::endl;

}