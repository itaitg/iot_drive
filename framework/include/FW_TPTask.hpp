
//
// Created by bender on 3/27/25.
#ifndef  ILRD_RD1645_FW_TPTASK_HPP
#define  ILRD_RD1645_FW_TPTASK_HPP



#include "ITaskArgs.hpp"
#include "ITPTask.hpp"

namespace ilrd
{
//task for the @Framework to run
class FW_TPTask final : public ITPTask
{
public:
    ///
    /// @param task_args_ arguments from @ITaskArgs
    explicit FW_TPTask(const std::shared_ptr<ITaskArgs>& task_args_);
    ///
    ///run for the specific task
    void Run() override;

    ~FW_TPTask() override = default;
    FW_TPTask(const FW_TPTask& other_) = delete;
    FW_TPTask& operator=(const FW_TPTask& other_) = delete;
    FW_TPTask(FW_TPTask&& other_) = delete;
    FW_TPTask& operator=(FW_TPTask&& other_) = delete;

private:
    std::shared_ptr<ITaskArgs> m_args;
};
}

#endif // ILRD_RD1645_FW_TPTASK_HPP
