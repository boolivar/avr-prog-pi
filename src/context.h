#ifndef CONTEXT_H
#define CONTEXT_H

#include "chipselect.h"
#include "dataformat.h"
#include "memoryprogrammer.h"
#include "outputcontroller.h"
#include "spi.h"

#include <memory>

class Context {
public:
    void setSpi(Spi* spi) { m_spi = makeUnique(spi); }
    Spi* getSpi() { return m_spi.get(); }

    void setChipSelect(ChipSelect* cs) { m_cs = makeUnique(cs); }
    ChipSelect* getChipSelect() { return m_cs.get(); }

    void setOutputController(OutputController* controller) { m_controller = makeUnique(controller); }
    OutputController* getOutputController() { return m_controller.get(); }

    void setMemoryProgrammer(MemoryProgrammer* memProg) { m_memProg = makeUnique(memProg); }
    MemoryProgrammer* getMemoryProgrammer() { return m_memProg.get(); }

    void setDataFormat(DataFormat* dataFormat) { m_dataFormat = makeUnique(dataFormat); }
    DataFormat* getDataFormat() { return m_dataFormat.get(); }

private:
    std::unique_ptr<Spi> m_spi;
    std::unique_ptr<ChipSelect> m_cs;
    std::unique_ptr<OutputController> m_controller;
    std::unique_ptr<MemoryProgrammer> m_memProg;
    std::unique_ptr<DataFormat> m_dataFormat;

    template<typename T>
    inline std::unique_ptr<T> makeUnique(T* p) { return std::unique_ptr<T>(p); }
};

#endif // CONTEXT_H
