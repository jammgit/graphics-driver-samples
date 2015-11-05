#pragma once

#include "d3dumddi_.h"
#include "RosUmdDevice.h"
#include "..\roscompiler\roscompiler.h"

class RosUmdShader
{
public:

    RosUmdShader(RosUmdDevice * pDevice, D3D10_SB_TOKENIZED_PROGRAM_TYPE Type)
        : m_pDevice(pDevice),
          m_ProgramType(Type),
          m_pCompiler(NULL)
    {
    }

    virtual ~RosUmdShader()
    {
    }

    static RosUmdShader* CastFrom(D3D10DDI_HSHADER);
    D3D10DDI_HSHADER CastTo() const;

    void Standup(const UINT * pCode, D3D10DDI_HRTSHADER hRTShader);
    virtual void Teardown();
    virtual void Update();

    RosUmdResource * GetCodeResource()
    {
        return &m_hwShaderCode;
    }

protected:

    D3D10_SB_TOKENIZED_PROGRAM_TYPE m_ProgramType;

    UINT *                          m_pCode;
    D3D10DDI_HRTSHADER              m_hRTShader;

    RosUmdDevice *                  m_pDevice;
    RosUmdResource                  m_hwShaderCode;
    UINT                            m_hwShaderCodeSize;
    
    RosCompiler *                   m_pCompiler;
};

inline RosUmdShader* RosUmdShader::CastFrom(D3D10DDI_HSHADER hShader)
{
    return static_cast< RosUmdShader* >(hShader.pDrvPrivate);
}

inline D3D10DDI_HSHADER RosUmdShader::CastTo() const
{
    return MAKE_D3D10DDI_HSHADER(const_cast< RosUmdShader* >(this));
}

class RosUmdPipelineShader : public RosUmdShader
{
public:

    RosUmdPipelineShader(RosUmdDevice *pDevice, D3D10_SB_TOKENIZED_PROGRAM_TYPE Type)
        : RosUmdShader(pDevice, Type)
    {
    }

    virtual ~RosUmdPipelineShader()
    {
    }

    static RosUmdPipelineShader* CastFrom(D3D10DDI_HSHADER);
    D3D10DDI_HSHADER CastTo() const;

    void Standup(const UINT * pCode, D3D10DDI_HRTSHADER hRT, const D3D11_1DDIARG_STAGE_IO_SIGNATURES * pSignatures);
    void Teardown();
    void Update();

private:

    UINT                            m_numInputSignatureEntries;
    D3D11_1DDIARG_SIGNATURE_ENTRY * m_pInputSignatureEntries;
    UINT                            m_numOutputSignatureEntries;
    D3D11_1DDIARG_SIGNATURE_ENTRY * m_pOutputSignatureEntries;

};

inline RosUmdPipelineShader* RosUmdPipelineShader::CastFrom(D3D10DDI_HSHADER hShader)
{
    return dynamic_cast<RosUmdPipelineShader*>(static_cast< RosUmdShader* >(hShader.pDrvPrivate));
}

inline D3D10DDI_HSHADER RosUmdPipelineShader::CastTo() const
{
    return MAKE_D3D10DDI_HSHADER(const_cast< RosUmdPipelineShader* >(this));
}

class RosUmdTesselationShader : public RosUmdShader
{
public:

    RosUmdTesselationShader(RosUmdDevice *pDevice, D3D10_SB_TOKENIZED_PROGRAM_TYPE Type)
        : RosUmdShader(pDevice, Type)
    {
    }

    virtual ~RosUmdTesselationShader()
    {
    }

    static RosUmdTesselationShader* CastFrom(D3D10DDI_HSHADER);
    D3D10DDI_HSHADER CastTo() const;

    void Standup(const UINT * pCode, D3D10DDI_HRTSHADER hRTShader, const D3D11_1DDIARG_TESSELLATION_IO_SIGNATURES * pSignatures);
    void Teardown();
    void Update();

private:

    UINT                                m_numInputSignatureEntries;
    D3D11_1DDIARG_SIGNATURE_ENTRY *     m_pInputSignatureEntries;
    UINT                                m_numOutputSignatureEntries;
    D3D11_1DDIARG_SIGNATURE_ENTRY *     m_pOutputSignatureEntries;
    UINT                                m_numPatchConstantSignatureEntries;
    D3D11_1DDIARG_SIGNATURE_ENTRY *     m_pPatchConstantSignatureEntries;

};

inline RosUmdTesselationShader* RosUmdTesselationShader::CastFrom(D3D10DDI_HSHADER hShader)
{
    return dynamic_cast<RosUmdTesselationShader*>(static_cast< RosUmdShader* >(hShader.pDrvPrivate));
}

inline D3D10DDI_HSHADER RosUmdTesselationShader::CastTo() const
{
    return MAKE_D3D10DDI_HSHADER(const_cast< RosUmdTesselationShader* >(this));
}
