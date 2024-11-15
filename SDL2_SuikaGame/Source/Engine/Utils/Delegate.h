#pragma once
#include <vector>
#include <functional>

#define FUNC_DECLARE_DELEGATE(DelegateName, ReturnType, ...) \
    using DelegateName = TDelegate<ReturnType(__VA_ARGS__)>;

#define FUNC_DECLARE_MULTICAST_DELEGATE(MulticastDelegateName, ReturnType, ...) \
    using MulticastDelegateName = TMulticastDelegate<ReturnType(__VA_ARGS__)>;

template <typename Signature>
class TDelegate;

template <typename ReturnType, typename... ParamTypes>
class TDelegate<ReturnType(ParamTypes...)>
{
    using FuncType = std::function<ReturnType(ParamTypes...)>;
    FuncType func;

public:
    void BindFunction(const FuncType& in_func)
    {
        func = in_func;
    }

    void UnBind()
    {
        func = nullptr;
    }

    [[nodiscard]] bool IsBound() const
    {
        return static_cast<bool>(func);
    }

    ReturnType Execute(ParamTypes... params) const
    {
        return func(std::forward<ParamTypes>(params)...);
    }

    bool ExecuteIfBound(ParamTypes... params) const
    {
        if (IsBound())
        {
            Execute(std::forward<ParamTypes>(params)...);
            return true;
        }
        return false;
    }
};

template <typename Signature>
class TMulticastDelegate;

template <typename ReturnType, typename... ParamTypes>
class TMulticastDelegate<ReturnType(ParamTypes...)>
{
    using FuncType = std::function<ReturnType(ParamTypes...)>;
    std::vector<FuncType> funcs;

public:
    // TODO: Handle을 반환해서 사용하도록 수정
    void AddFunction(const FuncType& in_func)
    {
        funcs.push_back(in_func);
    }

    // void Remove(Handle...);

    void Clear()
    {
        funcs.clear();
    }

    void Broadcast(ParamTypes... params) const
    {
        for (const auto& func : funcs)
        {
            func(std::forward<ParamTypes>(params)...);
        }
    }
};
