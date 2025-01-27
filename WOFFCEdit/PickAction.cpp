#include "PickAction.h"
#include "DirectXCollision.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

PickAction::PickAction()
{

}

PickAction::PickAction(char keybind, std::vector<DisplayObject>* displayList, float cooldownSeconds)
: m_keybind(keybind)
, m_displayList(displayList)
, m_cooldownSeconds(0.0f)
{

}

void PickAction::CooldownUpdate(float deltaTime)
{
    m_cooldownSeconds -= deltaTime;
}

bool PickAction::OnCooldown()
{
    return m_cooldownSeconds > 0.0f;
}

void PickAction::ResetCooldown()
{
    m_cooldownSeconds = m_cooldown;
}

bool PickAction::ExecuteAction(DirectX::SimpleMath::Vector2 screenPosition, RECT viewportRect, DirectX::SimpleMath::Matrix projectionMatrix, DirectX::SimpleMath::Matrix cameraViewMatrix)
{
    if (m_displayList == nullptr)
    {
        return false;
    }

    const Vector4 rayNear(screenPosition.x, screenPosition.y, 0.0f, 1.0f);
    const Vector4 rayFar(screenPosition.x, screenPosition.y, 1.0f, 1.0f);


    for (auto it = m_displayList->begin(); it < m_displayList->end(); ++it)
    {
        const Vector3 scale = { it->m_scale.x, it->m_scale.y, it->m_scale.z };
        const Vector3 translate = { it->m_position.x, it->m_position.y, it->m_position.z };

        //convert degrees into radians for rotation matrix
        const Vector4 rotate = Quaternion::CreateFromYawPitchRoll(it->m_orientation.y * XM_PI / 180.0f,
            it->m_orientation.x * XM_PI / 180.0f,
            it->m_orientation.z * XM_PI / 180.0f);

        const Matrix local = XMMatrixIdentity() * XMMatrixTransformation(g_XMZero, Quaternion::Identity, scale, g_XMZero, rotate, translate);

        //Unproject the points on the near and far plane, with respect to the matrix we just created.
        const Vector4 nearPoint = XMVector3Unproject(rayNear, 0.0f, 0.0f, viewportRect.right, viewportRect.bottom, 0.01f, 1000.0f, projectionMatrix, cameraViewMatrix, local);

        const Vector4 farPoint = XMVector3Unproject(rayFar, 0.0f, 0.0f, viewportRect.right, viewportRect.bottom, 0.01f, 1000.0f, projectionMatrix, cameraViewMatrix, local);

        //turn the transformed points into our picking vector. 
        Vector4 pickingVector = farPoint - nearPoint;
        pickingVector = XMVector3Normalize(pickingVector);
        Ray ray;
        ray.position = Vector3(nearPoint.x, nearPoint.y, nearPoint.z);
        ray.direction = Vector3(pickingVector.x, pickingVector.y, pickingVector.z);
        float distanceToObject;
        for (int j = 0; j < it->m_model.get()->meshes.size(); j++)
        {
            if (ray.Intersects(it->m_model->meshes[j]->boundingBox, distanceToObject))
            {
                it->m_selected = !it->m_selected;
                ResetCooldown();
                return true;
            }
        }

    }
    return false;

}