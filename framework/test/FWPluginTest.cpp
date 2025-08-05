//
// Created by bender on 3/30/25.

#include <iostream>
#include <optional>

#include "Factory.hpp"
#include "Handleton.hpp"
#include "Framework.hpp"
#include "IInputProxy.hpp"



class NBDReadArgs : public ilrd::ITaskArgs
{
public:
    NBDReadArgs(): m_str("Read"){}
    virtual ~NBDReadArgs() = default;
    NBDReadArgs(const NBDReadArgs& other_) = delete;
    NBDReadArgs& operator=(const NBDReadArgs& other_) = delete;
    NBDReadArgs(ITaskArgs&& other_) = delete;
    NBDReadArgs& operator=(NBDReadArgs&& other_) = delete;

    int GetKey(){return 0;}
    std::string& GetArgs(){return m_str;}
private:
    std::string m_str;
};
// offset, length (Getters / Setters / ctor)

class NBDWriteArgs : public ilrd::ITaskArgs
{
public:
    NBDWriteArgs(): m_str("Write"){}
    virtual ~NBDWriteArgs() = default;
    NBDWriteArgs(const NBDWriteArgs& other_) = delete;
    NBDWriteArgs& operator=(const NBDWriteArgs& other_) = delete;
    NBDWriteArgs(ITaskArgs&& other_) = delete;
    NBDWriteArgs& operator=(NBDWriteArgs&& other_) = delete;

    int GetKey(){return 1;}
    std::string& GetArgs(){return m_str;}
private:
    std::string m_str;

};
// offset, length,  char* (Getters / Setters / ctor)


class UpdatedCommandRead : public ilrd::ICommand
{
public:
    UpdatedCommandRead() = default;
    virtual ~UpdatedCommandRead() = default;

    UpdatedCommandRead(const UpdatedCommandRead& other_) = delete;
    UpdatedCommandRead& operator=(const UpdatedCommandRead& other_) = delete;
    UpdatedCommandRead(UpdatedCommandRead&& other_) = delete;
    UpdatedCommandRead& operator=(UpdatedCommandRead&& other_) = delete;

    std::optional<std::pair<const std::function<bool()>&, const std::chrono::milliseconds&>>
        Run(std::shared_ptr<ilrd::ITaskArgs> args_)
    {
        std::cout << "updated " <<dynamic_cast<NBDReadArgs*>(args_.get())
        ->GetArgs() << std::endl;
        return {};
    }
};




// Execute() which prints the fields


class UpdatedCommandWrite : public ilrd::ICommand
{
public:
    UpdatedCommandWrite() = default;
    virtual ~UpdatedCommandWrite() = default;

    UpdatedCommandWrite(const UpdatedCommandWrite& other_) = delete;
    UpdatedCommandWrite& operator=(const UpdatedCommandWrite& other_) = delete;
    UpdatedCommandWrite(UpdatedCommandWrite&& other_) = delete;
    UpdatedCommandWrite& operator=(UpdatedCommandWrite&& other_) = delete;

    std::optional<std::pair<const std::function<bool()>&, const std::chrono::milliseconds&>>
        Run(std::shared_ptr<ilrd::ITaskArgs> args_)
    {
        std::cout << "updated " << dynamic_cast<NBDWriteArgs*>(args_.get())
        ->GetArgs
        () << std::endl;
        return {};
    }
};
// Execute() which prints the fields



std::shared_ptr<ilrd::ICommand> CreateUpdatedReadCommand(){return
std::make_shared<UpdatedCommandRead>();}
std::shared_ptr<ilrd::ICommand> CreateUpdatedWriteCommand(){return
std::make_shared<UpdatedCommandWrite>();}





__attribute__((constructor))
void Start()
{
    std::cout << "plugins loaded" << std::endl;
    ilrd::Handleton::GetInstance<ilrd::Factory<int, ilrd::ICommand>>()->Register
        (0, CreateUpdatedReadCommand);
    ilrd::Handleton::GetInstance<ilrd::Factory<int, ilrd::ICommand>>()->Register
    (1, CreateUpdatedWriteCommand);
}



//class UpdatedReadCommand : public ICommand
//{
//    Execute(...);//Some other implementation the above (print something else)
//};
//
//ICommand* CreateUpdatedReadCommand(){return new UpdatedReadCommand;}
//
//# attribute compiler as dll constructor
//void SoMain()
//{
//    Factory::GetIntance()->Register(READ,UpdatedReadCommand);
//}
