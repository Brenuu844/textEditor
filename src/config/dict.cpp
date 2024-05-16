#include <cstddef>
#include <string>
#include <new>
#include "dict.h"

#include <iostream>

template <typename valueType>
class dictionary
{
private:
    struct Data
    {
        std::string key;
        valueType value;
    };

    struct Node
    {
        Data data;
        struct Node* next = 0;
    };

    size_t size = 0;
    Node* head = new (std::nothrow) Node;
    
    Node* getLastNode()
    {
        Node* currentNode = nullptr;

        if(head != nullptr)
        {
            currentNode = head;
            while (currentNode->next != nullptr)
            {
                currentNode = currentNode->next;
            }
            
        }

        return currentNode;
    }

public:
    size_t getSize()
    {
        return size;
    }

    bool add(std::string key, valueType value)
    {
        bool rc = false;

        if(head != nullptr)
        {
            Node* node = getLastNode();
            if(node != nullptr)
            {
                node->next = new (std::nothrow) Node;
                if(node->next != nullptr)
                {
                    node = node->next;
                    node->data.key = key;
                    node->data.value = value;
                    size++;
                }
            }
        }

        return rc;
    }

    bool isKey(std::string key)
    {
        bool rc = false;

        Node* currentNode = nullptr;

        if(head != nullptr)
        {
            currentNode = head;
            while (currentNode != nullptr)
            {
                if (currentNode->data.key == key)
                {
                    rc = true;
                    break;
                }
                currentNode = currentNode->next;
            }
            
        }

        return currentNode;

        return rc;
    }
    
    valueType getValueByKey(std::string key)
    {
        Node* currentNode = nullptr;

        if(head != nullptr)
        {
            currentNode = head;
            while (currentNode != nullptr)
            {
                if (currentNode->data.key == key)
                {
                    break;
                }
                currentNode = currentNode->next;
            }
            if (currentNode == nullptr)
            {
                dictErros error = keyNotFound;
                throw error;
            }
            
        }
        else
        {
            std::string error = "internal error";
            throw error;
        }

        return currentNode->data.value;
    }
};

int main(void)
{
    dictionary<std::string> dict = dictionary<std::string>();
    std::cout << dict.getSize() << std::endl;
    dict.add("key1", "value1");
    std::cout << dict.isKey("a") << std::endl;
    std::cout << dict.isKey("key1") << std::endl;
    try
    {
        std::cout << dict.getValueByKey("key1") << std::endl;
        std::cout << dict.getSize() << std::endl;
        std::cout << dict.getValueByKey("key2") << std::endl;
    }
    catch (dictErros error)
    {
        if (error == keyNotFound)
        {
            std::cout << "key not found" << std::endl;
        }
    }
    catch (std::string strError)
    {
        std::cout << strError;
    }

    return 0;
}