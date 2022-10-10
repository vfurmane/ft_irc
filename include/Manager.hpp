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

		Manager(void);
		Manager(const Manager &obj);
		~Manager(void);

		Manager			&operator=(const Manager &rhs);
		T				&operator[](const Key key)
		{
			this->c.at(key);
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
			return this->c.insert(key, value).first.second;
		}
		void			remove(const Key &key)
		{
			this->c.erase(key);
		}
		T				&get(const Key key)
		{
			(*this)[key];
		}

	protected:
		std::map<Key, T>	c;
};

#endif
