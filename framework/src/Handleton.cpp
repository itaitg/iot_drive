//
// Created by bender on 3/17/25.
// Approved by:


//////////////////include

#include "Handleton.hpp"

//////////////////static declarations

//////////////////constructors

//////////////////static implementations


std::unordered_map<const std::type_info*, std::shared_ptr<void>,
    ilrd::Handleton::HashFunc,ilrd::Handleton::EqualFunc>
    ilrd::Handleton::m_instances;
