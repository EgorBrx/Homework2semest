#pragma once
#include <iostream>
#include <stdexcept>
#include <assert.h>

template<typename data_type>
class Crcl_List
{
    struct Node {
        data_type data;
        Node* next;
        Node* back;

        Node(data_type data, Node* back = nullptr, Node* next = nullptr) : data(data), back(back), next(next)
        {

        }
        Node*& Next()
        {
            return next;
        }
        Node*& Back()
        {
            return back;
        }
    };

private:
    size_t size = 0;
    Node* root = nullptr;
    Node* end_ = nullptr;

    data_type GetValue(Node* root) {
        if (root != nullptr) {
            return root->data;
        }
        throw std::runtime_error("Root node is nullptr");
    }

    Node* GetNode(int32_t n, Node* root)
    {
        if (n == 0)  return root;
        if (n > 0)  return GetNode((n - 1) % size, root->next);
        if (n < 0)  return GetNode((n + 1) % size, root->back);

        return nullptr; 
    }

public:
    Crcl_List(data_type data)
    {
        root = new Node(data);
        end_ = root;
        size++;
    }

    ~Crcl_List()
    {
        size_t temp_size = size;
        for (size_t i = 0; i < temp_size; i++)
            this->extract();
    }
    data_type extract(int32_t n = 0)
    {
        Node* nodeToRemove = GetNode(n, root);

        if (nodeToRemove == nullptr)
        {
            throw std::runtime_error("Invalid index");
        }

        data_type extractedData = nodeToRemove->data;

        if (nodeToRemove == root) 
        {
            root = root->Next();
            if (*root->Next() == *root)
            {
                delete root;
                root = nullptr;
                size--;
                return extractedData;
            }
        }

        nodeToRemove->Back()->Next() = nodeToRemove->Next();
        nodeToRemove->Next()->Back() = nodeToRemove->Back();

        delete nodeToRemove;
        size--;

        return extractedData;
    }
    data_type GetValue(int32_t n = 0)
    {
        return GetValue(GetNode(n, root));
    }
    size_t GetSize(int32_t n = 0)
    {
        return size;
    }
    void Append(data_type data)
    {
        Node* newnode = new Node(data);
        if (size == 0) {
            root = newnode;
            end_ = newnode;
            newnode->Next() = root;
            newnode->Back() = root;
        }
        else {
            end_->Next() = newnode;
            newnode->Back() = end_;
            newnode->Next() = root;
            root->Back() = newnode;
            end_ = newnode;
        }
        size++;
    }

    void Insert(data_type data)
    {
        Node* newnode = new Node(data);
        if (size == 0) {
            root = newnode;
            end_ = newnode;
            newnode->Next() = root;
            newnode->Back() = root;
        }
        else {
            end_->Next() = newnode;
            newnode->Next() = root;
            root->Back() = newnode;
            newnode->Back() = end_;
            root = newnode;
        }
        size++;
    }
    data_type& operator[](int32_t index)
    {
        return GetNode(index, root)->data;
    }
    class Iterator {
    private:
        Node* current = nullptr;
        Node* begin = nullptr;
        size_t loop = 0;

    public:



        Iterator() = default; 

        Iterator(Node* node, Node* startNode, size_t loop) : current(node), begin(startNode), loop(loop)
        {

        }

        bool operator==(const Iterator& other) const {
            return (current == other.current) && (loop == other.loop);
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        Iterator operator++() {
            current = current->Next();
            if (current == begin) {
                loop++;
            }
            return *this;
        }
        Iterator& operator=(const Iterator& other)
        {
            if (this == &other) {
                return *this;
            }

            current = other.current;
            begin = other.begin;
            loop = other.loop;

            return *this;
        }
 


        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() {
            current = current->Back();
            if (current == begin && loop > 0) {
                loop--;
            }
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        data_type& operator*() const {
            return current->data;
        }
    };

    Iterator _begin() const
    {
        return Iterator(root, root, 0);
    }

    Iterator _end() const
    {
        return Iterator(root, root, 1);
    }
};

void test()
{
    Crcl_List<int> list(5);
    assert(list.GetSize() == 1);
    assert(list[0] == 5);

    list.Append(10);
    assert(list.GetSize() == 2);
    assert(list[1] == 10);

    list.Insert(3);
    assert(list.GetSize() == 3);
    assert(list[0] == 3);
    assert(list[1] == 5);
    assert(list[2] == 10);

    int extractedData = list.extract(1);
    assert(list.GetSize() == 2);
    assert(extractedData == 5);
    assert(list[0] == 3);
    assert(list[1] == 10);
}