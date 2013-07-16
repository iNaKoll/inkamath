#ifndef HPP_MAPSTACK
#define HPP_MAPSTACK

#include <list>
#include <map>
#include <stack>
#include <string>
#include <algorithm>
#include <boost/variant.hpp>
#include <boost/type_traits.hpp>
#include <cassert>

template <typename KeyType, typename ValueType, typename InternalIterator>
class mapstack_iterator_base {
	typedef mapstack_iterator_base self_type;
	typedef InternalIterator internal_iterator;
    internal_iterator m_it;
	typedef ValueType  value_type;
	typedef ValueType& reference;
	typedef ValueType* pointer;
public:
    mapstack_iterator_base(const internal_iterator& ai_it) :
        m_it(ai_it) {}

    reference operator*() {
        return m_it->top();
    }
	
    internal_iterator& operator->() {
        return m_it;
    }

    const internal_iterator& operator->() const {
        return m_it;
    }

    mapstack_iterator_base& operator++() {
        ++m_it;
        return *this;
    }

    mapstack_iterator_base operator++(int) {
        return mapstack_iterator_base(m_it++);
    }

	friend
    bool operator==(const self_type& x, const self_type& y) {
        return x.m_it == y.m_it;
    }
	
	friend
    bool operator!=(const self_type& x, const self_type& y) {
        return !(x == y);
    }
	
	friend
    bool operator<(const self_type& x, const self_type& y) {
        return x.m_it< y.m_it;
    }
	
	friend
    bool operator>(const self_type& x, const self_type& y) {
        return y < x;
    }
	
	friend
    bool operator<=(const self_type& x, const self_type& y) {
        return !(y < x);
    }
	
	friend
    bool operator>=(const self_type& x, const self_type& y) {
        return !(x < y);
    }
};

template <typename T1, typename T2>
class Mapstack {
public:
    typedef T1 key_type;
    typedef T2 value_type;

    Mapstack() {
        m_stack.push(std::list<key_type>());
    }
	
	typedef typename std::map<key_type, std::stack<value_type>>::iterator  		internal_iterator;
	typedef typename std::map<key_type, std::stack<value_type>>::const_iterator  internal_const_iterator;

    typedef mapstack_iterator_base<key_type, value_type, internal_iterator> 				iterator;
    typedef mapstack_iterator_base<key_type, const value_type, internal_const_iterator> 	const_iterator;
    typedef typename std::list<key_type>::const_iterator current_const_iterator;

    const_iterator begin() const {
        return m_map.begin();
    }

    const_iterator end() const {
        return m_map.end();
    }
    /*
    iterator begin()
    {
    	return m_map.begin();
    }

    iterator end()
    {
    	return m_map.end();
    }*/

    current_const_iterator CurrentBegin() const {
        return m_stack.top().begin();
    }

    current_const_iterator CurrentEnd() const {
        return m_stack.top().end();
    }

    void Push();
    void Pop();
    void Set(const key_type& ai_key, const value_type&  ai_value);

    template <typename T>
    bool Get(const key_type& ai_key, T& ao_value) const;

    bool Get(const key_type& ai_key, value_type& ao_value) const;


    void Clear();

private:
    std::stack<std::list<key_type>>  m_stack;
    std::map<key_type, std::stack<value_type>> m_map;
};

template <typename T1, typename T2>
void Mapstack<T1, T2>::Push()
{
    typename std::list<key_type>::iterator first = m_stack.top().begin();

    while(first != m_stack.top().end()) {
        m_map[*first].push(m_map[*first].top());
        ++first;
    }

    m_stack.push(std::list<key_type>());
}


template <typename T1, typename T2>
void Mapstack<T1, T2>::Pop()
{
    if(m_stack.top().empty()) {
        m_stack.pop();

        if(m_stack.empty()) {
            m_stack.push(std::list<key_type>());
            m_map.clear();
        }

        return;
    }


    typename std::list<key_type>::iterator first = m_stack.top().begin();

    while(first != m_stack.top().end()) {
        assert(!m_map.at(*first).empty());
        m_map.at(*first).pop();

        if(m_map.at(*first).empty()) {
            m_map.erase(*first);
        }

        ++first;
    }

    if(!m_stack.top().empty()) {
        m_stack.pop();

        if(m_stack.empty()) {
            m_stack.push(std::list<key_type>());
            m_map.clear();
            return;
        }
    }
}

template <typename T1, typename T2>
void Mapstack<T1, T2>::Set(const key_type& ai_key, const value_type&  ai_value)
{
    std::stack<value_type>& w_valueStack = m_map[ai_key];

    if(w_valueStack.empty()) {
        m_stack.top().push_back(ai_key);
        w_valueStack.push(ai_value);

    } else {
        if(std::find(m_stack.top().begin(), m_stack.top().end(), ai_key) == m_stack.top().end()) {
            m_stack.top().push_back(ai_key);
        }

        w_valueStack.top() = ai_value;
    }

    return;
}

template <typename T1, typename T2>
template <typename T>
bool Mapstack<T1, T2>::Get(const key_type& ai_key, T& ao_value) const
{
    value_type w_variant;
    bool w_bRet = Get(ai_key, w_variant) && boost::get<T>(&w_variant);

    if(w_bRet) {
        ao_value = boost::get<T>(w_variant);
    }

    return w_bRet;
}



template <typename T1, typename T2>
bool Mapstack<T1, T2>::Get(const key_type& ai_key, value_type& ao_value) const
{
    typename std::map<key_type, std::stack<value_type>>::const_iterator it = m_map.find(ai_key);
    bool w_bRet = it != m_map.end();

    if(w_bRet) {
        assert(!it->second.empty());
        ao_value = it->second.top();
    }

    return w_bRet;
}

template <typename T1, typename T2>
void Mapstack<T1, T2>::Clear()
{
    while(!m_stack.empty())
        m_stack.pop();

    m_map.clear();
    m_stack.push(std::list<key_type>());
    return;
}

#endif // MAPSTACK
