#pragma once

#include "constants.hpp"
#include "logger.hpp"
#include "resource.hpp"
#include <array>

namespace simq
{

template <std::size_t... Resources> class ResourceManager
{
  public:
    static constexpr std::size_t Size = sizeof...(Resources);
    ResourceManager (Logger &logger) : m_Logger(logger)
    {
        static_assert(sizeof...(Resources) == constants::ResourceTypes,
                      "Mismatch in resource number");
    }

  private:
    Logger &m_Logger;

  private:
    std::size_t m_Id                       = 0;
    std::array<Resource, Size> m_Resources = {
        {Resource(SmallLogger{m_Logger}, m_Id++, Resources)...}};
};

} // namespace simq
