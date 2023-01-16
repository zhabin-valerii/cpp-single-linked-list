#pragma once

#include <cassert>
#include <cstddef>
#include <iterator>
#include <string>
#include <utility>
#include <iostream>

template <typename Type>
class SingleLinkedList {
    struct Node {
        Node() = default;
        Node(const Type& val, Node* next = nullptr)
            : value(val), next_node(next) {}
        Type value{};
        Node* next_node = nullptr;
    };

    template<typename ValueType>
    class BasicIterator {
        friend class SingleLinkedList;

        explicit BasicIterator(Node* node) : node_(node) {}

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Type;
        using difference_type = std::ptrdiff_t;
        using pointer = ValueType*;
        using reference = ValueType&;

        BasicIterator() = default;

        BasicIterator(const BasicIterator<Type>& other) noexcept : node_(other.node_) {}

        BasicIterator& operator=(const BasicIterator& rhs) = default;

        [[nodiscard]] bool operator==(const BasicIterator<const Type>& rhs) const noexcept {
            return node_ == rhs.node_;
        }

        [[nodiscard]] bool operator!=(const BasicIterator<const Type>& rhs) const noexcept {
            return !(*this == rhs);
        }

        [[nodiscard]] bool operator==(const BasicIterator<Type>& rhs) const noexcept {
            return node_ == rhs.node_;
        }

        [[nodiscard]] bool operator!=(const BasicIterator<Type>& rhs) const noexcept {
            return !(*this == rhs);
        }

        BasicIterator& operator++() noexcept {
            assert(node_ != nullptr);
            node_ = node_->next_node;
            return *this;
        }

        BasicIterator operator++(int) noexcept {
            auto old_value(*this);
            ++(*this);
            return old_value;
        }

        [[nodiscard]] reference operator*() const noexcept {
            assert(node_ != nullptr);
            return node_->value;
        }

        [[nodiscard]] pointer operator->() const noexcept {
            assert(node_ != nullptr);
            return &node_->value;
        }

    private:
        Node* node_ = nullptr;
    };

public: 
      using value_type = Type;
      using reference = value_type&;
      using const_reference = const value_type&;
      using Iterator = BasicIterator<Type>;
      using ConstIterator = BasicIterator<const Type>;

      [[nodiscard]] Iterator begin() noexcept {
          return BasicIterator<Type>(head_.next_node);
      }

      [[nodiscard]] Iterator end() noexcept {
          return BasicIterator<Type>();
      }

      [[nodiscard]] ConstIterator begin() const noexcept {
          return BasicIterator<const Type>(head_.next_node);
      }

      [[nodiscard]] ConstIterator end() const noexcept {
          return BasicIterator<const Type>();
      }

      [[nodiscard]] ConstIterator cbegin() const noexcept {
          return BasicIterator<const Type>(head_.next_node);
      }

      [[nodiscard]] ConstIterator cend() const noexcept {
          return BasicIterator<const Type>();
      }

      [[nodiscard]] Iterator before_begin() noexcept {
          return BasicIterator<Type>(&head_);
      }

      [[nodiscard]] ConstIterator cbefore_begin() const noexcept {
          auto head_ptr = const_cast<Node*>(&head_);
          return BasicIterator<const Type>(head_ptr);
      }

      [[nodiscard]] ConstIterator before_begin() const noexcept {
          Node* head_ptr = const_cast<Node*>(&head_);
          return BasicIterator<const Type>(head_ptr);
      }

      SingleLinkedList() {
          head_.next_node = nullptr;
      }

      SingleLinkedList(std::initializer_list<Type> values) {
          if (values.begin() == values.end()) {
              return;
          }
          SingleLinkedList temp;
          for (auto it = values.size(); it > 0; --it) {
              temp.PushFront(values.begin()[it - 1]);
          }
          swap(temp);
      }


      SingleLinkedList(const SingleLinkedList& other) {
          assert(size_ == 0u && head_.next_node == nullptr);
          SingleLinkedList temp;
          auto it = temp.before_begin();
          for (const auto& list : other) {
              temp.InsertAfter(it, list);
              ++it;
          }
          swap(temp);
      }

      SingleLinkedList& operator=(const SingleLinkedList& rhs) {
          if (this != &rhs) {
              auto copy(rhs);
              swap(copy);
          }
          return *this;
      }

      void swap(SingleLinkedList& other) noexcept {
          std::swap(this->head_.next_node, other.head_.next_node);
          std::swap(this->size_, other.size_);
      }

      [[nodiscard]] size_t GetSize() const noexcept {
          return size_;
      }

      [[nodiscard]] bool IsEmpty() const noexcept {
          return size_ == 0;
      }

      void PushFront(const Type& value) {
          head_.next_node = new Node(value, head_.next_node);
          ++size_;
      }

      void PushBack(const Type& value) {
          if (head_.next_node == nullptr) {
              head_.next_node = new Node(value, nullptr);
          }
          else {
              Node* current = head_.next_node;
              while (current->next_node != nullptr)
              {
                  current = current->next_node;
              }
              current->next_node = new Node(value, nullptr);
          }
          ++size_;
      }

      Iterator InsertAfter(ConstIterator pos, const Type& value) {
          pos.node_->next_node = new Node(value, pos.node_->next_node);
          ++size_;
          return BasicIterator<Type>(pos.node_->next_node);
      }

      void PopFront() noexcept {
          assert(size_ != 0 && head_.next_node != nullptr);
          Node* temp = head_.next_node;
          head_.next_node = head_.next_node->next_node;
          delete temp;
          --size_;
      }

      Iterator EraseAfter(ConstIterator pos) noexcept {
          assert(pos.node_ != nullptr && pos.node_->next_node!= nullptr);
          Node* temp = pos.node_->next_node;
          pos.node_->next_node = pos.node_->next_node->next_node;
          delete temp;
          --size_;
          return BasicIterator<Type>(pos.node_->next_node);
      }

      void Clear() noexcept {
          while (head_.next_node != nullptr) {
              Node* temp = head_.next_node;
              head_.next_node = head_.next_node->next_node;
              delete temp;
          }
          size_ = 0u;
      }

      ~SingleLinkedList() {
          Clear();
      }

private:
    Node head_;
    size_t size_ = 0u;
};

template <typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename Type>
bool operator==(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    if (lhs.GetSize() != rhs.GetSize()) {
        return false;
    }
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
bool operator!=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(lhs == rhs);
}

template <typename Type>
bool operator<(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
bool operator<=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return rhs >= lhs;
}

template <typename Type>
bool operator>(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return rhs < lhs;
}

template <typename Type>
bool operator>=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return rhs < lhs || lhs == rhs;
}
