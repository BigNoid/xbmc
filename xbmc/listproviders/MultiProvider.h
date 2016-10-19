/*
 *      Copyright (C) 2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <vector>
#include <map>
#include "IListProvider.h"
#include "threads/CriticalSection.h"

typedef std::shared_ptr<IListProvider> IListProviderPtr;

/*!
 \ingroup listproviders
 \brief A listprovider that handles multiple individual providers.
 */
class CMultiProvider : public IListProvider
{
public:
  CMultiProvider(const TiXmlNode *first, int parentID);
  
  virtual bool Update(bool forceRefresh);
  virtual void Fetch(std::vector<CGUIListItemPtr> &items) const;
  virtual bool IsUpdating() const;
  virtual void Reset(bool immediately = false);
  virtual bool OnClick(const CGUIListItemPtr &item);
  virtual bool OnInfo(const CGUIListItemPtr &item);
  virtual bool OnContextMenu(const CGUIListItemPtr &item);
  
protected:
  std::vector<IListProviderPtr> m_providers;
  mutable std::map<CGUIListItem*, IListProviderPtr> m_itemMap; 
  CCriticalSection m_section; // protects m_itemMap
};
