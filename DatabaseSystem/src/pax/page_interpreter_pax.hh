/**
 *  @file   page_interpreter_pax.hh
 *  @author Nick Weber (nickwebe@pi3.informatik.uni-mannheim.de)
 *  @brief  A page interpreter class to operate on PAX pages
 *  @bugs   Currently no bugs known
 *  @todos  Currently no todos
 *
 *  @section DESCRIPTION
 *  TODO
 */
#ifndef PAGE_INTERPRETER_PAX_HH
#define PAGE_INTERPRETER_PAX_HH

#include "infra/webe/types.hh"


class PageInterpreterPAX {
  public:
    struct header_t {
        uint16_t _noRecords;      // number of records contained in this page
        uint16_t _freeSpace;      // total number of free bytes
        uint16_t _noAttributes;
        uint16_t _maxRecords;
    };

    struct slot_t {
      uint16_t _miniPageOffset; // offset to minipage
      uint16_t _miniPageAttrSize;   // size of the attributes on the mini page
    };

  public:
    PageInterpreterPAX();
    static void setPageSize(const size_t aPageSize);

  public:
    inline void  attach(byte* aPP);
    inline void  detach(); // set at least _pp to NULL, call not mandatory but adds safety

  public:
    void  initNewPage(byte* aPP, const uint_vt& aPartitionData); // combines initialization of fresh page with attach and partition into mini pages
    int  addNewRecord(const uint aRecordSize);

  public:
    inline const byte*     pagePtr() const { return _pp; }
    inline       byte*     pagePtr()       { return _pp; }
    inline const header_t* header() const { return _header; }
    inline       header_t* header()       { return _header; }
    inline uint  freeSpace() const { return header()->_freeSpace; }
    inline uint  noRecords() const { return header()->_noRecords; }
    inline uint  noAttributes() const { return header()->_noAttributes; }
    
    inline const uint16_t getAttrSize(const uint aAttrNo) const;
    inline       uint16_t getAttrSize(const uint aAttrNo);
    inline const uint16_t getMiniPageOffset(const uint aMiniPageNo) const;
    inline       uint16_t getMiniPageOffset(const uint aMiniPageNo);
    inline const byte* getMiniPagePointer(const uint aMiniPageNo) const;
    inline       byte* getMiniPagePointer(const uint aMiniPageNo);
    inline const slot_t& slot(const uint i) const { return _slot[- (int) i]; }
    inline       slot_t& slot(const uint i)       { return _slot[- (int) i]; }
    inline const uint16_t offset(const uint i) const { return _slot[- (int) i]._miniPageOffset; }
    inline       uint16_t offset(const uint i)       { return _slot[- (int) i]._miniPageOffset; }
    inline const size_t   getPageSize() const { return _pageSize; }
    inline       size_t   getPageSize()       { return _pageSize; }

  private:
    inline header_t* get_hdr_ptr() { return ((header_t*) (_pp + _pageSize - sizeof(header_t))); }
    inline slot_t*   get_slot_base_ptr() { return ((slot_t*) (_pp + _pageSize - sizeof(header_t) - sizeof(slot_t))); }
    void  pagePartition(const uint_vt& aAttrSizeVec); //partitions page into mini pages

  private:
    byte*     _pp;
    header_t* _header;
    slot_t*   _slot;  // new
    static bool _pageSizeSet;
    static size_t _pageSize;
};

void 
PageInterpreterPAX::attach(byte* aPP) {
  _pp = aPP;
  _header = get_hdr_ptr();
  _slot  = get_slot_base_ptr();
}

void
PageInterpreterPAX::detach() {
  _pp     = 0;
  _header = 0;
  _slot  = 0;
}

const uint16_t 
PageInterpreterPAX::getAttrSize(const uint aAttrNo) const { 
  if(aAttrNo >= noAttributes()) { 
    return 0; 
  }
  return slot(aAttrNo)._miniPageAttrSize; 
}

uint16_t
PageInterpreterPAX::getAttrSize(const uint aAttrNo) { 
  if(aAttrNo >= noAttributes()) { 
    return 0; 
  }
  return slot(aAttrNo)._miniPageAttrSize; 
}

const uint16_t 
PageInterpreterPAX::getMiniPageOffset(const uint aMiniPageNo) const { 
  if(aMiniPageNo >= noAttributes()) { 
    return 0; 
  }
  return slot(aMiniPageNo)._miniPageOffset; 
}

uint16_t
PageInterpreterPAX::getMiniPageOffset(const uint aMiniPageNo) { 
  if(aMiniPageNo >= noAttributes()) { 
    return 0; 
  }
  return slot(aMiniPageNo)._miniPageOffset; 
}

const byte* 
PageInterpreterPAX::getMiniPagePointer(const uint aMiniPageNo) const { 
  if(aMiniPageNo >= noAttributes()) { 
    return 0; 
  }
  return (_pp + slot(aMiniPageNo)._miniPageOffset); 
}

byte* 
PageInterpreterPAX::getMiniPagePointer(const uint aMiniPageNo) { 
  if(aMiniPageNo >= noAttributes()) { 
    return 0; 
  }
  return (_pp + slot(aMiniPageNo)._miniPageOffset); 
}

#endif
