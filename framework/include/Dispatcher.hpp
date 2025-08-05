
//
// Created by bender on 3/18/25.
#ifndef  ILRD_RD1645_DISPATCHER_HPP
#define  ILRD_RD1645_DISPATCHER_HPP


#include <queue>
#include <unordered_set>


namespace ilrd
{
template <typename EVENT>
class ACallback;

/// able to send @EVENT to objects that register
/// @tparam EVENT type of object to send/recieve
template <typename EVENT>
class Dispatcher
{
public:
    Dispatcher() = default;
    ~Dispatcher();
    Dispatcher(const Dispatcher& other_) = delete;
    Dispatcher& operator=(const Dispatcher& other_) = delete;
    /// Register a @Callback to run when the dispatcher notifies
    /// @param entry_
    void Register(ACallback<EVENT>& entry_);
    /// remove registration from the dispatcher
    /// @param entry_ the @Callback we want to remove
    void Unregister(ACallback<EVENT>& entry_);
    /// notify all the registered objects
    /// @param data_ the data to send
    void Notify(const EVENT& data_);
private:
    std::unordered_set<ACallback<EVENT>*> m_list;
    std::queue<std::pair<ACallback<EVENT>*, bool>> m_action;

    void UpdateList();
};

template <typename EVENT>
class ACallback
{
public:
    friend class Dispatcher<EVENT>;
    virtual ~ACallback();
    ACallback(const ACallback& other_) = default;
    ACallback& operator=(const ACallback& other_) = default;

    virtual void Notify(const EVENT& entry_) = 0;
    virtual void NotifyDeath() = 0;
protected:
    void SetDispatcher(Dispatcher<EVENT>* dispatcher_);
    ACallback() = default;
    Dispatcher<EVENT>* m_dispatcher;
};



template <typename EVENT, typename OBJ>
class Callback final : public ACallback<EVENT>
{
public:
    Callback(OBJ& obj_, void(OBJ::*notify_func_)(EVENT),
        void(OBJ::*death_func_)() = nullptr);
    ~Callback() override;
    Callback(const Callback& other_) = delete;
    Callback& operator=(const Callback& other_) = delete;

    void Notify(const EVENT& entry_) override;
    void NotifyDeath() override;
private:
    OBJ& m_obj;
    void (OBJ::*m_NotifyFunc)(EVENT);
    void (OBJ::*m_DeathFunc)();
};

//////////////////////ACallback

template <typename EVENT>
ACallback<EVENT>::~ACallback()
{
    if(this->m_dispatcher)
    {
        this->m_dispatcher->Unregister(*this);
    }
}

template<typename EVENT>
void ACallback<EVENT>::SetDispatcher(Dispatcher<EVENT>* dispatcher_)
{
    m_dispatcher = dispatcher_;
}

//////////////////////Callback


template <typename EVENT, typename OBJ>
Callback<EVENT, OBJ>::Callback(OBJ& obj_, void(OBJ::*notify_func_)(EVENT),
    void(OBJ::*death_func_)()): m_obj(obj_), m_NotifyFunc(notify_func_),
    m_DeathFunc(death_func_){}

template <typename EVENT, typename OBJ>
Callback<EVENT, OBJ>::~Callback()
{}

template <typename EVENT, typename OBJ>
void Callback<EVENT, OBJ>::Notify(const EVENT& entry_)
{
    (m_obj.*m_NotifyFunc)(entry_);
}

template <typename EVENT, typename OBJ>
void Callback<EVENT, OBJ>::NotifyDeath()
{
    this->m_dispatcher = nullptr;
    if(m_DeathFunc != nullptr)
    {
        (m_obj.*m_DeathFunc)();
    }
}


////////////////////////Dispatcher

template <typename EVENT>
Dispatcher<EVENT>::~Dispatcher()
{
    UpdateList();

    for(ACallback<EVENT>* element : m_list)
    {
        element->NotifyDeath();
    }
}

template <typename EVENT>
void Dispatcher<EVENT>::Register(ACallback<EVENT>& entry_)
{
    m_action.push({&entry_, true});
    entry_.SetDispatcher(this);
}

template <typename EVENT>
void Dispatcher<EVENT>::Unregister(ACallback<EVENT>& entry_)
{
    m_action.push({&entry_, false});
}

template <typename EVENT>
void Dispatcher<EVENT>::Notify(const EVENT& data_)
{
    UpdateList();

    for(ACallback<EVENT>* element : m_list)
    {
        element->Notify(data_);
    }
}

template <typename EVENT>
void Dispatcher<EVENT>::UpdateList()
{
    while(!m_action.empty())
    {
        std::pair<ACallback<EVENT>*, bool> pair = m_action.front();
        m_action.pop();
        if(pair.second)
        {
            m_list.insert(pair.first);
        }
        else
        {
            m_list.erase(pair.first);
        }
    }
}
}


#endif // ILRD_RD1645_DISPATCHER_HPP
