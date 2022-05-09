/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 13:19:57 by swquinc           #+#    #+#             */
/*   Updated: 2021/07/24 13:19:58 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
# include <list>
# include <forward_list>
# include <vector>
# include <iterator>

////// SFINAE c++98 Sub
//template<typename A>
//typename ft::enable_if<std::is_integral<A>::value, A>::type
//f(A t)
//{
//	std::cout << 1 << std::endl;
//	return(t);
//}
//
//template<typename A>
//typename ft::enable_if<!std::is_integral<A>::value>::type
//f(A t)
//{
//	std::cout << 2 << std::endl;
//}
struct p31 {
	char *t;
	p31(){
		t = new char;
	};
	p31(const p31& p) {
		t = new char;
		t[0] = *p.t;

	}
	~p31(){
		delete t;
		std::cout << "p31 destroyed" << std::endl;
	};
};
//class A {
//private:
//	std::string str;
//	int *n;
//	class B {
//		private:
//		int v;
//		public:
//		friend int ret(int);
//	};
//	int A::ret(int a){
//		this->v = a;
//		std::cout << a << std::endl;
//		return (this->v);
//	}
//public:
//	A(){
//		n = new int;
//	};
//	A(std::string str) {
//		this->str = str;
//		n = new int(42);
//	};
//	~A() {
//		delete n;
//	};
//	void pr() {
//		std::cout << str << " " << *n << std::endl;
//		ret(32);
//	};
//};

//template<typename I>
//void func(I a, typename I::input_iterator_tag* = NULL) {
//	std::cout << "dfgfd" << std::endl;
//}

void ok(){
	std::cout << "\e[1;92m [OK]\e[0m";
}

void fail() {
	std::cout << "\e[1;91m [FAIL]\e[0m";
//	exit(1);
}

int main()
{
	//////////////////
	///// test 1 /////
	//////////////////
	{
		std::cout << "\e[1;92mtest1:\e[0m";
		ft::vector<int> a(10);
		ft::vector<int>::iterator ait;
		std::vector<int> b(10);
		std::vector<int>::iterator bit;

		ait = a.begin();
		bit = b.begin();

		//// 1 checking assigment operator of iterator
		if (ait == a.begin())
			ok();
		else
			fail();
		//// 2 checking initiated values and iterator operator*
		if (*ait == *bit)
			ok();
		else
			fail();
		*ait = 42;
		*bit = 42;

		int q21 = *ait;
		int q22 = *ait;

		(void)q21;
		(void)q22;

		ft::vector<int>::iterator ait2(ait);
		std::vector<int>::iterator bit2(bit);

		(void)bit2;
		//// 3 checking iterator's operator* and iterator's copy constructor
		if (*ait2 == *bit)
			ok();
		else
			fail();
		//// 4 checking iterator's operator== and his method base(), also check memory handling
		if (ait2 == ait && ait2.base() == ait.base())
			ok();
		else
			fail();
		//// 5 checking iterator's operator!= and operator==, also check memory handling
		if (ait2 != a.end() && ait2 == a.begin())
			ok();
		else
			fail();
		ft::vector<ft::pair<int, std::string> > pa(5, ft::make_pair(42, "taraa"));
		ft::vector<ft::pair<int, std::string> >::iterator itp;
		//// 6 checking iterator's operator->, also check memory handling
		itp = pa.begin();
		if (itp->first == 42 && itp->second == "taraa")
			ok();
		else
			fail();

		std::cout << std::endl;
	}
	//////////////////
	///// test 2 /////
	//////////////////
	{
		std::cout << "\e[1;92mtest2:\e[0m";
		ft::vector<int> alala;

		//// 1 if no member
		if (alala.capacity() == 0)
			ok();
		else
			fail();
		alala.push_back(11);
		//// 2 if one member
		if (alala.capacity() == 1)
			ok();
		else
			fail();

		alala.push_back(22);
		//// 3 if two member
		if (alala.capacity() == 2)
			ok();
		else
			fail();

		alala.push_back(33);
		//// 4 if three member
		if (alala.capacity() == 4)
			ok();
		else
			fail();

		ft::vector<int>::iterator qweqwe;

		qweqwe = alala.begin();
		//// 5 checking iterator postfix operator++
		if (*qweqwe++ == 11 && *(qweqwe++) == 22 && *qweqwe == 33)
			ok();
		else
			fail();
		//// 6 iterator postfix operator++
		if ((*qweqwe)++ == 33 && *qweqwe == 34)
			ok();
		else
			fail();
		std::cout << std::endl;
	}
	//////////////////
	///// test 3 /////
	//////////////////
	{
		std::cout << "\e[1;92mtest3:\e[0m";
		ft::vector<int> a123;
		a123.push_back(5);
		a123.push_back(10);
		a123.push_back(15);
		ft::vector<int>::iterator qwe123;
		qwe123 = a123.begin();

		//// 1 checking iterator's prefix operator++
		if (*(++qwe123) == 10 && *qwe123 == 10 && ++*qwe123 == 11)
			ok();
		else
			fail();
		//// 2 checking iterator's prefix operator--
		if (*(--qwe123) == 5 && *qwe123 == 5 && --*qwe123 == 4)
			ok();
		else
			fail();
		//// 3 checking iterator's postfix operator--
		qwe123++;
		qwe123++;
		if (*qwe123-- == 15 && *qwe123 == 11 && (*qwe123)-- == 11 && *qwe123 == 10)
			ok();
		else
			fail();

		//// 4 checking iterator's operator- for iterators
		ft::vector<int> a312;
		a312.push_back(25);
		a312.push_back(50);
		a312.push_back(100);
		ft::vector<int>::iterator qwe312;
		ft::vector<int>::iterator qwe310;
		qwe312 = a312.begin();
		qwe310 = a312.end();
		if ((qwe312 - qwe310) == -3 && (qwe310 - qwe312) == 3)
			ok();
		else
			fail();
		//// 5 checking iterator's operator- and operator+ for n
		if (*(qwe310 - 1) == 100 && *(qwe312 + 1) == 50)
			ok();
		else
			fail();

		//// 6 checking binary + < > <= >=

		if (*(1 + qwe312) == 50 && qwe312 < qwe310 && qwe310 > qwe312 && qwe310 >= qwe312 &&
		qwe310 >= qwe310 && qwe312 <= qwe310 && qwe312 <= qwe312 && qwe312 != qwe310)
			ok();
		else
			fail();

		std::cout << std::endl;
	}
	//////////////////
	///// test 4 /////
	//////////////////
	{
		std::cout << "\e[1;92mtest4:\e[0m";

		ft::vector<int> h12;
		ft::vector<int>::iterator iter123;

		h12.push_back(21);
		h12.push_back(42);
		h12.push_back(84);
		iter123 = h12.begin();
		iter123++;
		--iter123;
		iter123 = h12.end();
		iter123--;

		////1 begin, end, ++ -- test, push_back
		if (*iter123 == 84 && h12.size() == 3)
			ok();
		else
			fail();

		////2 vector value constructor
		ft::vector<int> h21;
		ft::vector<std::string> h211(5, "taraa");
		ft::vector<std::string> h212(h211.begin(), h211.end());
		if (h211[0] == "taraa" && h211[4] == "taraa" && h211[5] != "taraa")
			ok();
		else
			fail();

		////3 vector iterator constructor
		h212.push_back("123");
		if (ft::distance(h212.begin(), h212.end()) == 6 && h212.capacity() == 10 &&
		h212[3] == "taraa" && h212[5] == "123" && h212.size() == 6)
			ok();
		else
			fail();

		////4 vector value constructor
		int m;
		long m1;
		char m2;

		m = 5;
		m1 = 5;
		m2 = 5;

		ft::vector<int> j12(m, m);
		ft::vector<int> j13(m1, m1);
		ft::vector<int> j14(m2, m2);
		ft::vector<int> j15(5, m2);

		if (j13[3] == 5 && j12[2] == 5 && j14[4] == 5 && j15[1] == 5)
			ok();
		else
			fail();

		//// 5 reverse_iterator
		ft::vector<int> ri;
		ri.push_back(10);
		ri.push_back(20);
		ri.push_back(30);
		ft::vector<int>::reverse_iterator rit;

		rit = ri.rbegin();
		rit++;
		if (*rit == 20 && *ri.rbegin() == 30 && *ri.begin() == 10 && *(--ri.end()) == 30 &&
		*(--ri.rend()) == 10)
			ok();
		else
			fail();
		////6 const_reverse_iterator
		const ft::vector<int> ri2(ri);

		ft::vector<int>::const_reverse_iterator rit2;

		rit2 = ri2.rbegin();
		rit2++;
		if (*rit2 == 20 && *ri2.rbegin() == 30 && *ri2.begin() == 10 && *(--ri2.end()) == 30 &&
		*(--ri2.rend()) == 10)
			ok();
		else
			fail();

		std::cout << std::endl;
	}
	//////////////////
	///// test 5 /////
	//////////////////
	{
		std::cout << "\e[1;92mtest5:\e[0m";

		std::vector<char> jk(10,  10);
		std::vector<std::string> jk2(10, "10");
		std::vector<long> jk3;
		std::vector<p31> jk4;
		ft::vector<char> lk(10, 10);
		ft::vector<std::string> lk2(10, "10");
		ft::vector<long> lk3;
		ft::vector<p31> lk4;
		/////1 max_size
		if (jk.max_size() == lk.max_size() && jk2.max_size() == lk2.max_size()
		&& jk3.max_size() == lk3.max_size() && jk4.max_size() == lk4.max_size())
			ok();
		else
			fail();

		////2 erase

		ft::vector<int> mh2;
		std::vector<int> mj2;

		mh2.push_back(1);
		mh2.push_back(2);
		mh2.push_back(3);
		mh2.push_back(4);
		mh2.push_back(5);
		mh2.push_back(6);
		mh2.push_back(7);
		mh2.push_back(8);
		mh2.push_back(9);
		mh2.push_back(10);

		mj2.push_back(1);
		mj2.push_back(2);
		mj2.push_back(3);
		mj2.push_back(4);
		mj2.push_back(5);
		mj2.push_back(6);
		mj2.push_back(7);
		mj2.push_back(8);
		mj2.push_back(9);
		mj2.push_back(10);

		ft::vector<int>::iterator ittter;
		std::vector<int>::iterator ittter2;

		ittter = mh2.end();
		ittter--;
		ittter--;
		ittter--;
		ittter--;
		ittter2 = mj2.end();
		ittter2--;
		ittter2--;
		ittter2--;
		ittter2--;

		if (*mh2.erase(mh2.begin(), ittter) == *mj2.erase(mj2.begin(), ittter2) &&
		mh2.capacity() == mj2.capacity() && mh2.size() == mj2.size())
		{
			std::vector<int>::iterator git = mj2.begin();

			for(ft::vector<int>::iterator it = mh2.begin(); it != mh2.end(); it++)
			{
				if (*it != *git)
					fail();
				git++;
			}
			ok();
		}
		else
			fail();

		////3 erase
		ft::vector<int> mh3;
		std::vector<int> mj3;

		mh3.push_back(1);
		mh3.push_back(2);
		mh3.push_back(3);
		mh3.push_back(4);
		mh3.push_back(5);
		mh3.push_back(6);
		mh3.push_back(7);
		mh3.push_back(8);
		mh3.push_back(9);
		mh3.push_back(10);

		mj3.push_back(1);
		mj3.push_back(2);
		mj3.push_back(3);
		mj3.push_back(4);
		mj3.push_back(5);
		mj3.push_back(6);
		mj3.push_back(7);
		mj3.push_back(8);
		mj3.push_back(9);
		mj3.push_back(10);

		ft::vector<int>::iterator ittterg;
		std::vector<int>::iterator ittterg2;

		ittterg = mh3.end();
		ittterg--;
		ittterg--;
		ittterg--;
		ittterg--;
		ittterg2 = mj3.end();
		ittterg2--;
		ittterg2--;
		ittterg2--;
		ittterg2--;

		if (*mh3.erase(ittterg, mh3.end()) == *mj3.erase(ittterg2, mj3.end()) &&
		mh3.capacity() == mj3.capacity() && mh3.size() == mj3.size())
		{
			std::vector<int>::iterator git = mj3.begin();

			for(ft::vector<int>::iterator it = mh3.begin(); it != mh3.end(); it++)
			{
				if (*it != *git)
					fail();
				git++;
			}
			ok();
		}
		else
			fail();
		//// erase 4

		ft::vector<int> mh4;
		std::vector<int> mj4;

		mh4.push_back(1);
		mh4.push_back(2);
		mh4.push_back(3);
		mh4.push_back(4);
		mh4.push_back(5);
		mh4.push_back(6);
		mh4.push_back(7);
		mh4.push_back(8);
		mh4.push_back(9);
		mh4.push_back(10);

		mj4.push_back(1);
		mj4.push_back(2);
		mj4.push_back(3);
		mj4.push_back(4);
		mj4.push_back(5);
		mj4.push_back(6);
		mj4.push_back(7);
		mj4.push_back(8);
		mj4.push_back(9);
		mj4.push_back(10);

		ft::vector<int>::iterator ittterg01;
		std::vector<int>::iterator ittterg02;

		ittterg01 = mh4.end();
		ittterg01--;
		ittterg01--;
		ittterg01--;
		ittterg01--;
		ittterg02 = mj4.end();
		ittterg02--;
		ittterg02--;
		ittterg02--;
		ittterg02--;

		if (*mh4.erase(ittterg01, --mh4.end()) == *mj4.erase(ittterg02, --mj4.end()) &&
		mh4.capacity() == mj4.capacity() && mh4.size() == mj4.size())
		{
			std::vector<int>::iterator git = mj4.begin();

			for(ft::vector<int>::iterator it = mh4.begin(); it != mh4.end(); it++)
			{
				if (*it != *git)
					fail();
				git++;
			}
			ok();
		}
		else
			fail();

		//// erase 5
		{
			ft::vector<int> mh5;
			std::vector<int> mj5;

			mh5.push_back(1);
			mh5.push_back(2);
			mh5.push_back(3);
			mh5.push_back(4);
			mh5.push_back(5);
			mh5.push_back(6);
			mh5.push_back(7);
			mh5.push_back(8);
			mh5.push_back(9);
			mh5.push_back(10);

			mj5.push_back(1);
			mj5.push_back(2);
			mj5.push_back(3);
			mj5.push_back(4);
			mj5.push_back(5);
			mj5.push_back(6);
			mj5.push_back(7);
			mj5.push_back(8);
			mj5.push_back(9);
			mj5.push_back(10);

			ft::vector<int>::iterator ittterg012;
			std::vector<int>::iterator ittterg021;

			ittterg012 = mh5.end();
			ittterg012--;
			ittterg012--;
			ittterg012--;
			ittterg012--;
			ittterg021 = mj5.end();
			ittterg021--;
			ittterg021--;
			ittterg021--;
			ittterg021--;

			if (*mh5.erase(ittterg012) == *mj5.erase(ittterg021) &&
			mh5.capacity() == mj5.capacity() && mh5.size() == mj5.size())
			{
				std::vector<int>::iterator git = mj5.begin();

				for(ft::vector<int>::iterator it = mh5.begin(); it != mh5.end(); it++)
				{
					if (*it != *git)
						fail();
					git++;
				}
				ok();
			}
			else
				fail();
		}
		////6 clear
		{
			ft::vector<int> pororo(10, 10);
			std::vector<int> pororo2(10, 10);

			pororo.clear();
			pororo2.clear();
			if (*pororo.end() == *pororo2.end() && pororo2.capacity() == pororo.capacity()
			&& pororo.size() == pororo2.size())
				ok();
			else
				fail();
		}
		std::cout << std::endl;
	}
	//////////////////
	///// test 6 /////
	//////////////////
	{
		std::cout << "\e[1;92mtest6:\e[0m";

		////1 assign
		{
			std::vector<int> hello(15, 15);
			std::vector<int> hell(50, 20);
			ft::vector<int> hello2(15, 15);
			ft::vector<int> hell2(50, 20);


			hello.assign(hell.begin(), hell.end());
			hello2.assign(hell2.begin(), hell2.end());

			if (hello.capacity() == hello2.capacity() && hello.size() == hello2.size())
			{
				std::vector<int>::iterator git2 = hello.begin();

				for(ft::vector<int>::iterator it = hello2.begin(); it != hello2.end(); it++)
				{
					if (*it != *git2)
						fail();
					git2++;
				}
				ok();
			}
			else
				fail();
		}
		////2 assign
		{
			std::vector<int> hello1(15, 15);
			std::vector<int> hell1(50, 20);
			ft::vector<int> hello3(15, 15);
			ft::vector<int> hell3(50, 20);


			hello1.assign(100, 1);
			hello3.assign(100, 1);


			if (hello1.capacity() == hello3.capacity() && hello1.size() == hello3.size())
			{
				std::vector<int>::iterator git3 = hello1.begin();

				for(ft::vector<int>::iterator it = hello3.begin(); it != hello3.end(); it++)
				{
					if (*it != *git3)
						fail();
					git3++;
				}
				ok();
			}
			else
				fail();
		}
		////3 assign
		{
			std::vector<int> hello11(15, 15);
			std::vector<int> hell111(2, 20);
			ft::vector<int> hello33(15, 15);
			ft::vector<int> hell33(2, 20);


			hello11.assign(hell111.begin(), hell111.end());
			hello33.assign(hell33.begin(), hell33.end());


			if (hello11.capacity() == hello33.capacity() && hello11.size() == hello33.size())
			{
				std::vector<int>::iterator git4 = hello11.begin();

				for(ft::vector<int>::iterator it = hello33.begin(); it != hello33.end(); it++)
				{
					if (*it != *git4)
						fail();
					git4++;
				}
				ok();
			}
			else
				fail();
		}
		////4 assign
		{
			std::vector<int> hello10(15, 15);
			ft::vector<int> hello30(15, 15);


			hello10.assign(2, 1);
			hello30.assign(2, 1);


			if (hello10.capacity() == hello30.capacity() && hello10.size() == hello30.size()) {
				std::vector<int>::iterator git6 = hello10.begin();

				for (ft::vector<int>::iterator it = hello30.begin(); it != hello30.end(); it++) {
					if (*it != *git6)
						fail();
					git6++;
				}
				ok();
			} else
				fail();

			ft::vector<int> max12(10, 10);
		}


		//// 5 reserve if n > capacity
		{
			ft::vector<int> vft;

			vft.push_back(1);
			int *rft = &vft[0];
			vft.reserve(10);
			if (rft != &vft[0] && vft.capacity() == 10 && vft.size() == 1)
				ok();
			else
				fail();
		}
		//// 6 reserve if n <= capacity
		{
			ft::vector<int> vft;

			vft.push_back(1);
			vft.push_back(2);
			vft.push_back(3);
			vft.push_back(4);
			int *rft = &vft[0];
			vft.reserve(2);

			if (rft == &vft[0] && vft.capacity() == 4 && vft.size() == 4)
				ok();
			else
				fail();
		}
		std::cout << std::endl;
	}
	//////////////////
	///// test 7 /////
	//////////////////
	{
		std::cout << "\e[1;92mtest7:\e[0m";
		////1 resize
		{
			std::vector<int> a(8, 1);
			ft::vector<int> a2(8, 1);

			a.resize(17, 5);
			a2.resize(17, 5);
			ft::vector<int>::iterator it2 = a2.begin();
			if (a.capacity() == a2.capacity() && a.size() == a2.size())
			{
				for(std::vector<int>::iterator it = a.begin(); it != a.end(); it++)
				{
					if(*it != *it2)
						fail();
					it2++;
				}
				ok();
			}
			else
				fail();
		}
		////2 resize
		{
			std::vector<int> a(8, 1);
			ft::vector<int> a2(8, 1);
			int *ptr;

			ptr = &a2[0];
			a.resize(5, 5);
			a2.resize(5, 5);
			ft::vector<int>::iterator it2 = a2.begin();
			if (a.capacity() == a2.capacity() && a.size() == a2.size() && ptr == &a2[0])
			{
				for(std::vector<int>::iterator it = a.begin(); it != a.end(); it++)
				{
					if(*it != *it2)
						fail();
					it2++;
				}
				ok();
			}
			else
				fail();
		}
		////3 resize
		{
			std::vector<int> a(8, 1);
			ft::vector<int> a2(8, 1);
			int *ptr;

			ptr = &a2[0];
			a.resize(16, 5);
			a2.resize(16, 5);
			ft::vector<int>::iterator it2 = a2.begin();
			if (a.capacity() == a2.capacity() && a.size() == a2.size() && ptr != &a2[0])
			{
				for(std::vector<int>::iterator it = a.begin(); it != a.end(); it++)
				{
					if(*it != *it2)
						fail();
					it2++;
				}
				ok();
			}
			else
				fail();
		}
		////4 resize
		{
			std::vector<int> a(8, 1);
			ft::vector<int> a2(8, 1);
			int *ptr;

			ptr = &a2[0];
			a.resize(100, 5);
			a2.resize(100, 5);
			ft::vector<int>::iterator it2 = a2.begin();
			if (a.capacity() == a2.capacity() && a.size() == a2.size() && ptr != &a2[0])
			{
				for(std::vector<int>::iterator it = a.begin(); it != a.end(); it++)
				{
					if(*it != *it2)
						fail();
					it2++;
				}
				ok();
			}
			else
				fail();
		}
		////5 resize
		{
			std::vector<int> a;
			ft::vector<int> a2;
			int *ptr;

			a.push_back(10);
			a.push_back(20);
			a.push_back(30);
			a2.push_back(10);
			a2.push_back(20);
			a2.push_back(30);

			ptr = &a2[0];
			a.resize(0, 5);
			a2.resize(0, 5);
			ft::vector<int>::iterator it2 = a2.begin();
			if (a.capacity() == a2.capacity() && a.size() == a2.size() && ptr == &a2[0])
			{
				for(std::vector<int>::iterator it = a.begin(); it != a.end(); it++)
				{
					if(*it != *it2)
						fail();
					it2++;
				}
				ok();
			}
			else
				fail();
		}
		////6 resize
		{
			std::vector<int> a(15, 1);
			ft::vector<int> a2(15, 1);
			int *ptr;

			ptr = &a2[0];
			a.resize(14, 5);
			a2.resize(14, 5);
			ft::vector<int>::iterator it2 = a2.begin();
			if (a.capacity() == a2.capacity() && a.size() == a2.size() && ptr == &a2[0])
			{
				for(std::vector<int>::iterator it = a.begin(); it != a.end(); it++)
				{
					if(*it != *it2)
						fail();
					it2++;
				}
				ok();
			}
			else
				fail();
		}
		std::cout << std::endl;
	}
	//////////////////
	///// test 8 /////
	//////////////////
	{
		std::cout << "\e[1;92mtest8:\e[0m";
		////1 insert
		{
			std::vector<int> a1;
			ft::vector<int> a2;

			a1.push_back(11);
			a1.push_back(22);
			a1.push_back(33);
			a1.push_back(44);

			a2.push_back(11);
			a2.push_back(22);
			a2.push_back(33);
			a2.push_back(44);


			a1.insert(++a1.begin(), 3, 100);
			a2.insert(++a2.begin(), 3, 100);
			ft::vector<int>::iterator it2 = a2.begin();
			if (a1.size() == a2.size() && a1.capacity() == a2.capacity())
			{
				for(std::vector<int>::iterator it = a1.begin(); it != a1.end(); it++)
				{
					if(*it != *it2)
						fail();
					it2++;
				}
				ok();
			}
			else
				fail();
		}
		////2 insert memmove
		{
			std::vector<int> a1;
			ft::vector<int> a2;

			a1.push_back(11);
			a1.push_back(22);
			a1.push_back(33);
			a1.push_back(44);

			a2.push_back(11);
			a2.push_back(22);
			a2.push_back(33);
			a2.push_back(44);


			a1.insert(++a1.begin(), a1.begin(), a1.end());
			a2.insert(++a2.begin(), a2.begin(), a2.end());
			ft::vector<int>::iterator it2 = a2.begin();

			if (a1.size() == a2.size() && a1.capacity() == a2.capacity())
			{
				for(std::vector<int>::iterator it = a1.begin(); it != a1.end(); it++)
				{
					//								std::cout << "std: " << *it << " ft: " << *it2 << std::endl;
					if(*it != *it2)
						fail();
					it2++;
				}
				ok();
			}
			else
				fail();
		}
		//// 3 insert
		{
			std::vector<int> a1;
			ft::vector<int> a2;

			a1.push_back(11);
			a1.push_back(22);
			a1.push_back(33);
			a1.push_back(44);

			a2.push_back(11);
			a2.push_back(22);
			a2.push_back(33);
			a2.push_back(44);

			a1.insert(--a1.end(), a1.begin(), a1.end());
			a2.insert(--a2.end(), a2.begin(), a2.end());
			ft::vector<int>::iterator it2 = a2.begin();

			if (a1.size() == a2.size() && a1.capacity() == a2.capacity())
			{
				for(std::vector<int>::iterator it = a1.begin(); it != a1.end(); it++)
				{
					//								std::cout << "std: " << *it << " ft: " << *it2 << std::endl;
					if(*it != *it2)
						fail();
					it2++;
				}
				ok();
			}
			else
				fail();
		}
		//// 4 insert
		{
			std::vector<int> a1;
			std::vector<int> b1;
			ft::vector<int> a2;
			ft::vector<int> b2;
			std::vector<int>::iterator ita1;
			ft::vector<int>::iterator ita2;

			a1.push_back(11);
			a1.push_back(22);
			a1.push_back(33);
			a1.push_back(44);

			a2.push_back(11);
			a2.push_back(22);
			a2.push_back(33);
			a2.push_back(44);

			b1.push_back(54);
			b1.push_back(21);
			b1.push_back(69);
			b1.push_back(42);

			b2.push_back(54);
			b2.push_back(21);
			b2.push_back(69);
			b2.push_back(42);

			ita1 = a1.begin();
			ita2 = a2.begin();

			ita1 += 2;
			ita2 += 2;

			a1.insert(ita1, b1.begin(), b1.end());
			a2.insert(ita2, b2.begin(), b2.end());
			ft::vector<int>::iterator it2 = a2.begin();

			if (a1.size() == a2.size() && a1.capacity() == a2.capacity())
			{
				for(std::vector<int>::iterator it = a1.begin(); it != a1.end(); it++)
				{
					if(*it != *it2)
					{
						fail();
						break ;
					}
					it2++;
				}
				ok();
			}
			else
				fail();
		}

		//// 5 insert
		{
			//		namespace ft = std;
			std::vector<int> a1;
			ft::vector<int> a2;
			std::vector<int>::iterator ita1;
			ft::vector<int>::iterator ita2;

			a1.push_back(11);
			a1.push_back(22);
			a1.push_back(33);
			a1.push_back(44);
			a1.push_back(55);
			a1.push_back(66);
			a1.push_back(77);
			a1.push_back(88);

			a2.push_back(11);
			a2.push_back(22);
			a2.push_back(33);
			a2.push_back(44);
			a2.push_back(55);
			a2.push_back(66);
			a2.push_back(77);
			a2.push_back(88);

			ita1 = a1.end();
			ita2 = a2.end();


			a1.insert(ita1, a1.begin(), a1.begin() + 4);
			a2.insert(ita2, a2.begin(), a2.begin() + 4);
			ft::vector<int>::iterator it2 = a2.begin();

			if (a1.size() == a2.size() && a1.capacity() == a2.capacity())
			{
				for(std::vector<int>::iterator it = a1.begin(); it != a1.end(); it++)
				{
					//				std::cout << "std: " << *it << " ft: " << *it2 << std::endl;
					if(*it != *it2)
						fail();
					it2++;
				}
				ok();
			}
			else
				fail();
		}
		//// 6 insert
		{
			//		namespace ft = std;
			std::vector<int> a1;
			ft::vector<int> a2;
			std::vector<int>::iterator ita1;
			ft::vector<int>::iterator ita2;

			a1.push_back(11);
			a1.push_back(22);
			a1.push_back(33);
			a1.push_back(44);
			a1.push_back(55);
			a1.push_back(66);
			a1.push_back(77);
			a1.push_back(88);

			a2.push_back(11);
			a2.push_back(22);
			a2.push_back(33);
			a2.push_back(44);
			a2.push_back(55);
			a2.push_back(66);
			a2.push_back(77);
			a2.push_back(88);

			ita1 = a1.begin() + 4;
			ita2 = a2.begin() + 4;

			a1.insert(ita1, a1.begin(), a1.end());
			a2.insert(ita2, a2.begin(), a2.end());
			ft::vector<int>::iterator it2 = a2.begin();

			if (a1.size() == a2.size() && a1.capacity() == a2.capacity())
			{
				for(std::vector<int>::iterator it = a1.begin(); it != a1.end(); it++)
				{
					if(*it != *it2)
					{
						fail();
						break ;
					}
					it2++;
				}
				ok();
			}
			else
				fail();
		}
		std::cout << std::endl;
	}
	//////////////////
	///// test 9 /////
	//////////////////
	{
//		std::cout << "\e[1;92mtest9:\e[0m";
//		////1 swap
//		{
//			ft::vector<int> a(10, 5);
//			ft::vector<int> b(10, 1);
//			ft::vector<int>::iterator it;
//
//			a.swap(b);
//			for(it = a.begin(); it != a.end(); it++)
//			{
//				std::cout << *it << std::endl;
//			}
//		}
	}
}