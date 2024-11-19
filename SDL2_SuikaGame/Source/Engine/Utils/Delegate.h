#pragma once
#include <unordered_map>
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


class MulticastDelegateHandle
{
public:
    using HandleType = std::uint64_t;

    MulticastDelegateHandle() : id(0) {}
    explicit MulticastDelegateHandle(HandleType val) : id(val) {}

    [[nodiscard]] bool IsValid() const { return id != 0; }
    void Invalidate() { id = 0; }

    bool operator==(const MulticastDelegateHandle& other) const { return id == other.id; }
    bool operator!=(const MulticastDelegateHandle& other) const { return !(*this == other); }

    static MulticastDelegateHandle Create()
    {
        static HandleType next_handle = 1;
        return MulticastDelegateHandle(next_handle++);
    }

    [[nodiscard]] HandleType GetID() const { return id; }  // 해시 함수를 위해 추가

private:
    HandleType id;
};

// MulticastDelegateHandle을 위한 해시 함수
template <>
struct std::hash<MulticastDelegateHandle> {
    std::size_t operator()(const MulticastDelegateHandle& h) const noexcept
    {
        return std::hash<MulticastDelegateHandle::HandleType>{}(h.GetID());
    }
};


template <typename Signature>
class TMulticastDelegate;

template <typename ReturnType, typename... ParamTypes>
class TMulticastDelegate<ReturnType(ParamTypes...)>
{
public:
    using FuncType = std::function<ReturnType(ParamTypes...)>;

private:
    std::unordered_map<MulticastDelegateHandle, FuncType> funcs;

public:
    MulticastDelegateHandle AddFunction(const FuncType& in_func)
    {
        MulticastDelegateHandle handle = MulticastDelegateHandle::Create();
        funcs[handle] = in_func;
        return handle;
    }

    void Remove(const MulticastDelegateHandle& handle)
    {
        funcs.erase(handle);
    }

    void Clear()
    {
        funcs.clear();
    }

    void Broadcast(ParamTypes... params) const
    {
        auto copy_funcs = funcs;
        for (const auto& [handle, func] : copy_funcs)
        {
            func(params...);
        }
    }
};
