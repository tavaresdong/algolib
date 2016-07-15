#ifndef _BOUNDED_PQ_H_
#define _BOUNDED_PQ_H_

#include <functional>
#include <utility>
#include <iostream>
#include <vector>


namespace algo
{
	// This is an implementation of an Max Heap, meaning the top item has the
	// Maximum priority
	template <typename T>
	class PriorityQueue {
	public:
		PriorityQueue();
		void push(T elem, double priority);
		void pop();
		const T& top() const;
		size_t size() const { return heap.size(); }
		bool empty() const { return heap.empty(); }

	private:
		void siftUp(size_t i);
		void siftDown(size_t i);
		std::vector<std::pair<double, T> > heap;
	};

	template <typename T>
	PriorityQueue<T>::PriorityQueue() { }

	template <typename T>
	void PriorityQueue<T>::push(T elem, double priority)
	{
		heap.push_back(std::make_pair<double, T>(std::move(priority), 
											     std::move(elem)));
		siftUp(heap.size() - 1);
	}

	template <typename T>
	void PriorityQueue<T>::pop()
	{
		if (heap.empty())
			throw std::out_of_range("priority queue is empty");
		std::swap(heap[0], heap[heap.size() - 1]);
		heap.pop_back();
		siftDown(0);
	}

	template <typename T>
	const T& PriorityQueue<T>::top() const
	{
		if (heap.empty())
			throw std::out_of_range("priority queue is empty");
		return heap[0].second;
	}

	template <typename T>
	void PriorityQueue<T>::siftDown(size_t i)
	{
		while (i * 2 + 1 < heap.size())
		{
			size_t left = i * 2 + 1;
			size_t right = i * 2 + 2;
			size_t toswap = left;
			if (right < heap.size() && heap[right].first > heap[left].first)
				toswap = right;
			if (heap[i].first < heap[toswap].first)
			{
				std::swap(heap[i], heap[toswap]);
				i = toswap;
			}
			else
			{
				break;
			}
		}
	}

	template<typename T>
	void PriorityQueue<T>::siftUp(size_t i)
	{
		if (i < 0 || i >= heap.size())
			throw std::out_of_range("index out of bound");

		while (i > 0)
		{
			int parent = i / 2;
			if (heap[i].first > heap[parent].first)
			{
				std::swap(heap[i], heap[parent]);
				i = parent;
			}
			else
			{
				break;
			}
		}
	}

	void testPriorityQueue()
	{
		PriorityQueue<std::string> pq;
		pq.push("15", 15);
		pq.push("13", 13);
		pq.push("9", 9);
		pq.push("5", 5);
		pq.push("12", 12);
		pq.push("8", 8);
		pq.push("7", 7);
		pq.push("4", 4);
		pq.push("0", 0);
		pq.push("6", 6);
		pq.push("2", 2);
		pq.push("1", 1);

		while (!pq.empty())
		{
			auto val = pq.top();
			std::cout << val << std::endl;
			pq.pop();
		}
		int i;
		cin >> i;
	}
}

#endif