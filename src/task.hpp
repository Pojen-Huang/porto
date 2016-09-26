#pragma once

#include <string>
#include <vector>

#include "util/namespace.hpp"
#include "util/path.hpp"
#include "util/cred.hpp"
#include "util/unix.hpp"
#include "container.hpp"
#include "cgroup.hpp"
#include "env.hpp"
#include "filesystem.hpp"

struct TTaskEnv {
    std::shared_ptr<TContainer> CT;
    TClient *Client;
    TFile PortoInit;
    TMountNamespace Mnt;
    TEnv Env;
    bool TripleFork;
    bool QuadroFork;
    TNamespaceSnapshot ParentNs;
    std::vector<TDevice> Devices;
    std::vector<std::string> Autoconf;
    bool NewMountNs;
    std::vector<TCgroup> Cgroups;
    TCred Cred;

    TUnixSocket Sock, MasterSock;
    TUnixSocket Sock2, MasterSock2;
    int ReportStage = 0;

    int SchedPolicy = -1;
    int SchedPriority = 0;
    int SchedNice = 0;

    TError Start();
    void StartChild();

    TError ConfigureChild();
    TError ChildApplyLimits();
    TError WriteResolvConf();
    TError SetHostname();

    TError WaitAutoconf();
    TError ChildExec();

    void ReportPid(pid_t pid);
    void Abort(const TError &error);
};
