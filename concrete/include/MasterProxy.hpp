
//
// Created by bender on 4/20/25.
#ifndef  ILRD_RD1645_MASTERPROXY_HPP
#define  ILRD_RD1645_MASTERPROXY_HPP

#include <memory>

#include "UDP_socket.hpp"
#include "IInputProxy.hpp"

namespace ilrd
{

struct MinionArgs
{
    MinionArgs(size_t offset_, size_t length_, UID id_, std::shared_ptr<char[]> buffer_ = nullptr);
    size_t m_offset;
    size_t m_length;
    UID m_id;
    std::shared_ptr<char[]> m_buffer;
};


class MasterProxy final : public IInputProxy
{
public:
    MasterProxy();
    ~MasterProxy() override = default;

    std::shared_ptr<ATaskArgs> GetTaskArgs(int fd_, MODE mode_) override;
    void SendReadResponse(bool status_, UID id_, size_t length_, char* buffer_ = nullptr);
    void SendWriteResponse(bool status_, UID id_);
    int  GetSocketFD() const;

    MasterProxy(const MasterProxy& other_) = delete;
    MasterProxy& operator=(const MasterProxy& other_) = delete;
    MasterProxy(MasterProxy&& other_) = delete;
    MasterProxy& operator=(MasterProxy&& other_) = delete;

private:
    std::mutex m_mutex;
    UDP_Socket m_socket;

};
}

#endif // ILRD_RD1645_MASTERPROXY_HPP
