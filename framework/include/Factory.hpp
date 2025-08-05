
//
// Created by bender on 3/12/25.
#ifndef  ILRD_RD1645_FACTORY_HPP
#define  ILRD_RD1645_FACTORY_HPP


#include <functional>
#include <memory>


namespace ilrd
{
///Able to construct objects during runtime,
///must be used with @Handleton
template <typename KEY, typename BASE, typename ...ARGS>
class Factory
{
public:
    /// enter new @OBJECT to create
    /// @param key_ key associated with @OBJECT
    /// @param func_ how to create @OBJECT
    void Register(KEY key_, std::function<std::shared_ptr<BASE>(ARGS...)> func_);
    /// Create the @OBJECT
    /// @param key_ key associated with @OBJECT
    /// @param arguments_ arguments for the constructed @OBJECT (leave empty
    // if none)
    std::shared_ptr<BASE> Create(KEY key_, ARGS... arguments_);
    friend class Handleton;
    ~Factory() = default;
private:
    Factory() = default;
    std::unordered_map<KEY, std::function<std::shared_ptr<BASE>(ARGS...)>> m_map;
};

template <typename KEY, typename BASE, typename ... ARGS>
void Factory<KEY, BASE, ARGS...>::Register(KEY key_,
    std::function<std::shared_ptr<BASE>(ARGS...)> func_)
{
    m_map[key_] = func_;
}

template <typename KEY, typename BASE, typename ... ARGS>
std::shared_ptr<BASE> Factory<KEY, BASE, ARGS...>::Create(KEY key_,
    ARGS... arguments_)
{
    return m_map.at(key_)(arguments_...);
}
}

#endif // ILRD_RD1645_FACTORY_HPP
