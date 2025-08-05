
//
// Created by bender on 4/6/25.
#ifndef  ILRD_RD1645_NBDPROXY_HPP
#define  ILRD_RD1645_NBDPROXY_HPP


#include <map>
#include <memory>
#include <linux/nbd.h>

#include "Dispatcher.hpp"
#include "IInputProxy.hpp"
#include "NBD.hpp"

namespace ilrd
{

enum NBDKEY
{
    AREAD,
    AWRITE
};

struct NBDArgs
{
    NBDArgs(size_t offset_, size_t length, const std::shared_ptr<char[]>& buffer_ = nullptr);
    size_t m_offset;
    size_t m_length;
    std::shared_ptr<char[]> m_buffer;
};


class NBDProxy final : public IInputProxy
{
public:
    explicit NBDProxy(NBD& nbd_);
    ~NBDProxy() override = default;

    std::shared_ptr<ATaskArgs> GetTaskArgs(int fd_, MODE mode_) override;
    void RegisterForNewTaskArgs(ACallback<const std::shared_ptr<ATaskArgs>&>&
    callback_);
    void Reply(const UID& handle_, bool status_, size_t count_data_, const std::shared_ptr<char[]>& data_);

    NBDProxy(const NBDProxy& other_) = delete;
    NBDProxy& operator=(const NBDProxy& other_) = delete;
    explicit NBDProxy(IInputProxy&& other_) = delete;
    NBDProxy& operator=(NBDProxy&& other_) = delete;

private:
    NBD& m_nbd;
    Dispatcher<const std::shared_ptr<ATaskArgs>&> m_dispatcher;
    std::mutex m_mutex;
    std::map<UID, std::array<char, sizeof(nbd_request::handle)>> m_map;
};
}

#endif // ILRD_RD1645_NBDPROXY_HPP
