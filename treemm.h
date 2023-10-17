#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>


struct Node;
//struct Pair;
template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator()
        { 
            m_isItValid = false;
           //it = nullptr;   
        }

        Iterator(std::vector<ValueType>& v)
        {
            m_isItValid = true;
            vptr = &v;
            m_pos = 0;
            //it = v.begin();
            //currentPair = getCurrentPair();
        }

        ValueType& get_value() const
        {
            return (*vptr)[m_pos];
        }

        bool is_valid() const
        {
            if (m_isItValid == false) {
                return false;
            }
            else {
                return true;
            }
        }

        void advance()
        {
            m_pos++;
            if (m_pos >= vptr->size()) {
                m_isItValid = false;
            }
            // Replace this line with correct code.
        }

      private:
          //std::vector<ValueType>::iterator it
          std::vector<ValueType>* vptr;
          bool m_isItValid;
          int m_pos; 
          //Node* curr;
          //Pair currentPair;
    };

    TreeMultimap()
    {
        root = nullptr;
        // Replace this line with correct code.
    }

    ~TreeMultimap()
    {
        Deforestation(root);
        // Replace this line with correct code.
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        ValueType copy = value;
        if (root == nullptr) {
            root = new Node(key);
            root->m_map.push_back(copy);
            return;
        }

        Node* curr = root;
        for (;;)
        {
            if (curr->key == key) {
                curr->m_map.push_back(copy);
                return;
            }
            if (key > curr->key) {
                if (curr->right != nullptr) {
                    curr = curr->right;
                }
                else {
                    curr->right = new Node(key);
                    curr->right->m_map.push_back(copy);
                    return;
                }
            }
            else if (key < curr->key) {
                if (curr->left != nullptr) {
                    curr = curr->left;
                }
                else {
                    curr->left = new Node(key);
                    curr->left->m_map.push_back(copy);
                    return;
                }
            }
        }
        // Replace this line with correct code.
    }

    Iterator find(const KeyType& key) const
    {
        Node* curr = root;
        while (curr != nullptr) {
            if (curr->key == key) {
                //vector<ValueType>::Iterator itReturn;
                return Iterator(curr->m_map);
            }
            if (key < curr->key) {
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }
        }
        return Iterator();  // Replace this line with correct code.
    }

  private:
      /*struct Pair
      {
          Pair(KeyType x, ValueType y)
          {
              first = x;
              second = y;
          }
          KeyType first;
          ValueType second;

      };*/
      struct Node
      {
          Node(KeyType k)
          {
              key = k;
              right = nullptr;
              left = nullptr;
          }
          std::vector<ValueType> m_map;
          KeyType key;
          Node* left;
          Node* right;
      };
      void Deforestation(Node* current)
      {
          //Node* curr = root;
          if (current == nullptr) {
              return;
          }
          Deforestation(current->left);
          Deforestation(current->right);
          delete current; 

      }
      /*Pair* getCurrPair()
      {
          return &(Node::m_map[0]);
      }*/
      Node* root;
};

#endif // TREEMULTIMAP_INCLUDED
