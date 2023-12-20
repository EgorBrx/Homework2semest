#pragma once
template <typename Iterator, typename Compare>
void bubbleSort(Iterator begin, Iterator end, Compare comp) {
    for (auto i = begin; i != end; ++i) {
        for (auto j = begin; j != std::prev(end, std::distance(begin, i)); ++j) {
            if (comp(*j, *std::next(j))) {
                std::iter_swap(j, std::next(j));
            }
        }
    }
}


template <typename RandomAccessIterator, typename Compare>
void heapify(RandomAccessIterator begin, RandomAccessIterator end, RandomAccessIterator rootIdx, Compare comp) {
    auto size = std::distance(begin, end);
    auto largest = rootIdx;
    auto leftChildIdx = std::next(begin, 2 * std::distance(begin, rootIdx) + 1);
    auto rightChildIdx = std::next(begin, 2 * std::distance(begin, rootIdx) + 2);

    if (leftChildIdx < end && comp(*leftChildIdx, *largest)) {
        largest = leftChildIdx;
    }

    if (rightChildIdx < end && comp(*rightChildIdx, *largest)) {
        largest = rightChildIdx;
    }

    if (largest != rootIdx) {
        std::iter_swap(rootIdx, largest);
        heapify(begin, end, largest, comp);
    }
}
template <typename RandomAccessIterator, typename Compare>
void heapSort(RandomAccessIterator begin, RandomAccessIterator end, Compare comp) {
    for (auto i = std::prev(end); i != begin; --i) {
        heapify(begin, end, i, comp);
    }

    for (auto i = std::prev(end); i != begin; --i) {
        std::iter_swap(begin, i);
        heapify(begin, i, begin, comp);
    }
}

template <typename Iterator, typename Compare>
void merge(Iterator begin, Iterator middle, Iterator end, Compare comp) {
    std::vector<typename std::iterator_traits<Iterator>::value_type> left(std::make_move_iterator(begin), std::make_move_iterator(middle));
    std::vector<typename std::iterator_traits<Iterator>::value_type> right(std::make_move_iterator(middle), std::make_move_iterator(end));

    auto leftIt = left.begin();
    auto rightIt = right.begin();
    auto mergedIt = begin;

    while (leftIt != left.end() && rightIt != right.end()) {
        if (comp(*leftIt, *rightIt)) {
            *mergedIt = std::move(*leftIt);
            ++leftIt;
        }
        else {
            *mergedIt = std::move(*rightIt);
            ++rightIt;
        }
        ++mergedIt;
    }

    std::move(leftIt, left.end(), mergedIt);
    std::move(rightIt, right.end(), mergedIt);
}
template <typename Iterator, typename Compare>
void mergeSort(Iterator begin, Iterator end, Compare comp) {
    if (std::distance(begin, end) > 1) {
        auto middle = std::next(begin, std::distance(begin, end) / 2);

        mergeSort(begin, middle, comp);
        mergeSort(middle, end, comp);

        merge(begin, middle, end, comp);
    }
}