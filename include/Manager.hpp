#ifndef MANAGER_HPP
# define MANAGER_HPP

# include <map>

template < class Key, class T, class Container = std::map<Key, T> >
class Manager
{
	protected:
		typedef Container container_type;

	public:
		typedef typename container_type::iterator		iterator;
		typedef typename container_type::const_iterator	const_iterator;
		typedef typename std::map<Key ,T>::size_type	size_type;

		Manager(void) : c()
		{
		}

		Manager(const Manager &obj) : c(obj.c)
		{
			*this = obj;
		}
		~Manager(void)
		{
		}

		Manager			&operator=(const Manager &rhs)
		{
			(void)rhs;
			return *this;
		}
		T				&operator[](const Key key)
		{
			return this->c.at(key);
		}

		iterator		begin(void)
		{
			return this->c.begin();
		}
		const_iterator	begin(void) const
		{
			return this->c.begin();
		}
		iterator		end(void)
		{
			return this->c.end();
		}
		const_iterator	end(void) const
		{
			return this->c.end();
		}
		void			clear()
		{
			this->c.clear();
		}

		T				&add(const Key &key, const T &value)
		{
			return this->c.insert(std::make_pair(key, value)).first->second;
		}
		void			remove(const Key &key)
		{
			this->c.erase(key);
		}
		T				&get(const Key &key)
		{
			return (*this)[key];
		}
		bool			has(const Key &key) const
		{
			return this->c.find(key) != this->c.end();
		}
		bool empty() const
		{
			return this->c.empty();
		}
		size_type size() const
		{
			return this->c.size();
		}

	protected:
		std::map<Key, T>	c;
};

#endif
