#pragma once
#include "MapSite.h"

class Wall : public MapSite
{
public:
  Wall();
  virtual void enter() override;
  virtual SiteType type() override { return SiteType::Wall; };
};
