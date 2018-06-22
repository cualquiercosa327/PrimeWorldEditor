#include "CRadiusSphereExtra.h"
#include "Core/Render/CDrawUtil.h"
#include "Core/Render/CRenderer.h"

CRadiusSphereExtra::CRadiusSphereExtra(CScriptObject* pInstance, CScene* pScene, CScriptNode* pParent)
    : CScriptExtra(pInstance, pScene, pParent)
{
    mObjectType = pInstance->ObjectTypeID();
    CStructPropertyNew* pProperties = pInstance->Template()->Properties();

    switch (mObjectType)
    {
    case 0x63: // Repulsor (MP1)
        mRadius = CFloatRef(pInstance, pProperties->ChildByID(3));
        break;

    case 0x68: // RadialDamage (MP1)
        mRadius = CFloatRef(pInstance, pProperties->ChildByID(0x4));
        break;

    case FOURCC('REPL'): // Repulsor (MP2/MP3)
    case FOURCC('RADD'): // RadialDamage (MP2/MP3/DKCR)
        mRadius = CFloatRef(pInstance, pProperties->ChildByID(0x78C507EB));
        break;
    }
}

void CRadiusSphereExtra::AddToRenderer(CRenderer* pRenderer, const SViewInfo& rkViewInfo)
{
    if (!rkViewInfo.GameMode && (rkViewInfo.ShowFlags & eShowObjectGeometry) && mRadius.IsValid() && mpParent->IsVisible() && mpParent->IsSelected())
    {
        CAABox BoundingBox = Bounds();

        if (rkViewInfo.ViewFrustum.BoxInFrustum(BoundingBox))
            pRenderer->AddMesh(this, -1, BoundingBox, false, eDrawMesh);
    }
}

void CRadiusSphereExtra::Draw(FRenderOptions /*Options*/, int /*ComponentIndex*/, ERenderCommand /*Command*/, const SViewInfo& /*rkViewInfo*/)
{
    glBlendFunc(GL_ONE, GL_ZERO);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);

    CDrawUtil::DrawWireSphere(mpInstance->Position(), mRadius, Color());
}

CColor CRadiusSphereExtra::Color() const
{
    switch (mObjectType)
    {
    // Repulsor
    case 0x63:
    case 0x5245504C:
        return CColor::skGreen;

    // RadialDamage
    case 0x68:
    case 0x52414444:
        return CColor::skRed;

    default:
        return CColor::skWhite;
    }
}

CAABox CRadiusSphereExtra::Bounds() const
{
    CAABox Bounds = CAABox::skOne * 2.f * mRadius;
    Bounds += mpParent->AbsolutePosition();
    return Bounds;
}
