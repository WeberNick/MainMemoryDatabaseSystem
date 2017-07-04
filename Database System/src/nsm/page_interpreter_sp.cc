#include "page_interpreter_sp.hh"

PageInterpreterSP::PageInterpreterSP() : _pp(NULL), _header(NULL), _slots(0) {
}

void 
PageInterpreterSP::attach(byte* aPP) {
  _pp = aPP;
  _header = get_hdr_ptr();
  _slots  = get_slot_base_ptr();
}

void
PageInterpreterSP::detach() {
  _pp     = 0;
  _header = 0;
  _slots  = 0;
}

void 
PageInterpreterSP::initNewPage(byte* aPP) {
  if(aPP)
  {
    attach(aPP);
    header()->_noRecords   = 0;
    header()->_freeSpace   = (PAGE_SIZE_GLOBAL - sizeof(header_t));
    header()->_nextFreeRecord = 0;
    header()->_placeholder = 0;
  }
}

byte* 
PageInterpreterSP::addNewRecord(const uint aRecordSize) {
  const uint lRecordSize = ((aRecordSize + 7) & ~(uint) 0x07); // adjust for 8 byte alignment
  const uint lTotalSize = lRecordSize + sizeof(slot_t);        // add space for one new slot 

  byte*   lResultRecord = 0;

  if(lTotalSize <= freeSpace()) {
    lResultRecord = pagePtr() + header()->_nextFreeRecord;
    header()->_nextFreeRecord += lRecordSize;          // remember pointer to next free record
    header()->_freeSpace -= lTotalSize;
    slot(noRecords())._offset = lResultRecord - pagePtr();  // store offset of new record in slot
    header()->_noRecords += 1;
  }
  return lResultRecord;
}

