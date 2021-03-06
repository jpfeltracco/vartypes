//========================================================================
//  This software is free: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License Version 3,
//  as published by the Free Software Foundation.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  Version 3 in the file COPYING that came with this distribution.
//  If not, see <http://www.gnu.org/licenses/>.
//========================================================================
/*!
  \file    VarList.h
  \brief   C++ Interface: VarList
  \author  Stefan Zickler, (C) 2008
*/

#ifndef DATAGROUP_H_
#define DATAGROUP_H_
#include "VarType.h"
#include <vector>
using namespace std;
namespace VarTypes {
  
  /*!
    \class  VarList
    \brief  This is the list type of the VarTypes system
    \author Stefan Zickler, (C) 2008
    \see    VarTypes.h
  
    VarList allows the storage of an ordered list of children nodes.
  
    If you don't know what VarTypes are, please see \c VarTypes.h 
  */
  
  class VarList;
  typedef shared_ptr<VarList> VarListPtr;
  
  class VarList : public VarType
  {
    Q_OBJECT
  protected:
    vector<VarPtr> list;
  signals:
    void childAdded(VarPtr child);
    void childRemoved(VarPtr child);
  public:
    /// Creates an empty VarList
    VarList(string _name="") : VarType(_name) {
    };
    virtual ~VarList() {
      list.clear();
    };
  

    
    /// this will always return the empty string ""
    virtual string getString() const { return ""; }
  
    /// this will clear the list
    virtual void resetToDefault() {lock(); for (unsigned int i=0;i<list.size();i++) { emit(childRemoved(list[i])); } list.clear();  unlock(); };
  
    /// prints the label and number of elements
    virtual void printdebug() const { printf("VarList named %s containing %zu element(s)\n",getName().c_str(), list.size()); }
  
    /// adds a VarType item to the end of the list.
    int addChild(VarPtr child) { lock(); list.push_back(child); emit(childAdded(child)); unlock(); changed(); return (list.size()-1);}
    bool removeChild(VarPtr child) {
      lock();
      vector<VarPtr> newlist;
      unsigned int n=list.size();
      bool found=false;
      for (unsigned int i=0;i<n;i++) {
        if (list[i]!=child) {
          newlist.push_back(list[i]);
        } else {
          found=true;
        }
      }
      if (found) {
        emit(childRemoved(child));
        list=newlist;
        changed();
      }
      unlock();
      return found;
    };
  
    virtual VarTypeId getType() const { return VARTYPE_ID_LIST; } ;
  
    /// returns the number of children of this list
    virtual int getChildrenCount() const
    {
      int res;
      lock();
      res = list.size();
      unlock();
      return res;
    }
  
    /// removes all children, by actually deleting them in memory
    /// note that this is recursive.
    /// use it to un-allocate entire hierarchies from memory
    virtual void deleteAllChildren() {
      lock();
      int n = list.size();
      for (int i = 0; i < n ; i++) {
        if (list[i]!= nullptr) {
          list[i]->deleteAllChildren();
        }
      }
      list.clear();
      unlock();
    }

    /// returns a vector of all children in the order that they occur in internally
    virtual vector<VarPtr> getChildren() const
    {
      lock();
      vector<VarPtr> l = list;
      unlock();
      return l;
    }
  
    /// Finds a child based on the label of 'other'
    /// If the child is not found then other is returned
    /// However, if the child *is* found then other will be *deleted* and the child will be returned!
    VarPtr findChildOrReplace(VarPtr other) {
      VarPtr data = findChild(other->getName());
      if (data.get()!=0) {
        return data;
      } else {
        addChild(other);
        return other;
      }
    }
  
    /// Finds a child based on the label of 'other'
    /// If the child is not found then other is returned
    /// However, if the child *is* found then other will be *deleted* and the child will be returned!
    template <class VCLASSPTR> 
    VCLASSPTR findChildOrReplace(VCLASSPTR other) {
      VCLASSPTR data = (VCLASSPTR)findChild(other->getName());
      if (data.get()!=0) {
        return data;
      } else {
        addChild(other);
        return other;
      }
    }
  
  
  #ifndef VDATA_NO_XML
  protected:
    virtual void readChildren(XMLNode & us)
    {
      lock();
      int before=list.size();
      list=readChildrenHelper(us, list, false, false);
      int after=list.size();
      if (after > before) {
        for (int i=before; i < after; i++) {
          emit(childAdded(list[i]));
        }
      }
      unlock();
      changed();
    }
  #endif
  
  //Qt model/view gui stuff:
  public:
  virtual QWidget * createEditor(const VarItemDelegate * delegate, QWidget *parent, const QStyleOptionViewItem &option) {
    (void)delegate;
    (void)option;
    (void)parent;
    return 0;
  }

  };
};

#endif /*DATAGROUP_H_*/
