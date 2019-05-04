#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>

#include "spi.h"
#include "chipselect.h"
#include "memoryprogrammer.h"

class Context {
public:
    void setSpi(Spi* spi) { m_spi = makeUnique(spi); }
    Spi* getSpi() { return m_spi.get(); }

    void setChipSelect(ChipSelect* cs) { m_cs = makeUnique(cs); }
    ChipSelect* getChipSelect() { return m_cs.get(); }

    void setMemoryProgrammer(MemoryProgrammer* memProg) { m_memProg = makeUnique(memProg); }
    MemoryProgrammer* getMemoryProgrammer() { return m_memProg.get(); }

private:
    std::unique_ptr<Spi> m_spi;
    std::unique_ptr<ChipSelect> m_cs;
    std::unique_ptr<MemoryProgrammer> m_memProg;

    template<typename T>
    inline std::unique_ptr<T> makeUnique(T* p) { return std::unique_ptr<T>(p); }
};

#endif // CONTEXT_H
