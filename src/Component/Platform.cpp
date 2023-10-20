#include "Platform.h"

Platform::Platform()
{
  
}

Platform::Platform(bool isActive, bool isUsable, std::vector<glm::vec4> travelVectors,
    std::vector<glm::vec4> travelPoints, bool repetable, bool returnsOnDeactivation,
    bool loop): _travelVectors(travelVectors), _travelPoints(travelPoints),
    _repetable(repetable), _returnsOnDeactivation(returnsOnDeactivation),
    _loop(loop)
{
    _isActive = isActive;
    _isUsable = isUsable;
}

std::shared_ptr<Component> Platform::GetCopyComponent()
{
    std::shared_ptr<Component> copyComponent = std::make_shared<Platform>(Platform(_isActive, _isUsable, _travelVectors,
        _travelPoints, _repetable, _returnsOnDeactivation, _loop));

    return copyComponent;
}

void Platform::Start()
{
    Reset();
    GenerateTravelPoints();
}

void Platform::SetUp()
{
    if(_isActive) _start = true;
    if (!_travelPoints.size())
    {
        _tmpMovementVector = glm::vec3(0.0f);
        m_gameObject->m_transform->SetPosition(glm::vec4(m_gameObject->m_transform->GetPosition(), 1));
        _actualLocation = 0;
        _direction = 1;
        _timer = 0.0f;
        AddTravelVector(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        GenerateTravelPoints();
    }
    else {
        Start();
    }
}

void Platform::Run()
{
    Move();
}

void Platform::Return()
{
    if (_returnsOnDeactivation && _start)
    {
        if (_actualLocation == 0 && _timer == 0)
        {
            if (_actualLocation == 0)
            {
                SetIsUsable(true);
            }
        }
        
        if (!_reachedCheckpoint)
        {
            int nextLocation = _actualLocation + _direction;
            if (nextLocation < _travelPoints.size() && nextLocation >= 0)
            {
                _timer += TIME.GetDeltaTime();
                m_gameObject->m_transform->SetPosition(Lerp(glm::vec3(_travelPoints[_actualLocation]), glm::vec3(_travelPoints[nextLocation]), _timer * (1 / _travelPoints[nextLocation].w)));
                if (CloseVectors(m_gameObject->m_transform->GetPosition(), glm::vec3(_travelPoints[nextLocation])))
                {
                    _actualLocation += _direction;
                    _direction = -1;
                    _reachedCheckpoint = true;
                    _timer = 0;
                }
            }
        }
        else {
            int nextLocation = _actualLocation + _direction;
            if (nextLocation < _travelPoints.size() && nextLocation >= 0)
            {
                _timer += TIME.GetDeltaTime();
                m_gameObject->m_transform->SetPosition(Lerp(glm::vec3(_travelPoints[_actualLocation]), glm::vec3(_travelPoints[nextLocation]), _timer * (1 / _travelPoints[nextLocation].w)));
                if (CloseVectors(m_gameObject->m_transform->GetPosition(), glm::vec3(_travelPoints[nextLocation])))
                {
                    m_gameObject->UpdateColliders();
                    _actualLocation += _direction;
                    _timer = 0.0f;
                    _tmpMovementVector = glm::vec3(0.0f);
                }
            }
        }
    }
    /*
    if (_returnsOnDeactivation && _start)
    {
        if (_actualLocation == 0 && _timer == 0)
        {
            SetIsUsable(true);
        }
        if (!_reachedCheckpoint)
        {
            _timer -= TIME.GetDeltaTime();
            int nextLocation = _actualLocation + _direction;
            if (nextLocation < _travelPoints.size() && nextLocation >= 0)
            {
                m_gameObject->m_transform->SetPosition(Lerp(glm::vec3(_travelPoints[_actualLocation]), glm::vec3(_travelPoints[nextLocation]), _timer * (1 / _travelPoints[nextLocation].w)));
                if (CloseVectors(m_gameObject->m_transform->GetPosition(), glm::vec3(_travelPoints[_actualLocation])))
                {
                    _direction = -1;
                    _reachedCheckpoint = true;
                    _timer = 0;
                }
            }
        }
        else {
            int nextLocation = _actualLocation + _direction;
            if (nextLocation < _travelPoints.size() && nextLocation >= 0)
            {
                _timer += TIME.GetDeltaTime();
                m_gameObject->m_transform->SetPosition(Lerp(glm::vec3(_travelPoints[_actualLocation]), glm::vec3(_travelPoints[nextLocation]), _timer * (1 / _travelPoints[nextLocation].w)));
                if (CloseVectors(m_gameObject->m_transform->GetPosition(), glm::vec3(_travelPoints[nextLocation])))
                {
                    m_gameObject->UpdateColliders();
                    _actualLocation += _direction;
                    _timer = 0.0f;
                    _tmpMovementVector = glm::vec3(0.0f);
                }
            }
        }
    }
    */
}

void Platform::Move()
{
    int nextLocation = _actualLocation + _direction;
    if (nextLocation < _travelPoints.size() && nextLocation >= 0)
    {
        _timer += TIME.GetDeltaTime();
        m_gameObject->m_transform->SetPosition(Lerp(glm::vec3(_travelPoints[_actualLocation]), glm::vec3(_travelPoints[nextLocation]), _timer * (1/_travelPoints[nextLocation].w)));
        if (CloseVectors(m_gameObject->m_transform->GetPosition(), glm::vec3(_travelPoints[nextLocation])))
        {
            _actualLocation += _direction;
            _timer = 0.0f;
            _tmpMovementVector = glm::vec3(0.0f);
            m_gameObject->UpdateColliders();
            //StartCoroutine("Delay");
        }
    } else if (_repetable)
    {
        _direction *= -1;
    } else if (_loop)
    {
        _actualLocation = 0;
    }
}

void Platform::ActionStop()
{
    if (_returnsOnDeactivation)
    {
        if (_timer == 0)
        {
            _direction = -1;
            _reachedCheckpoint = true;
        }
        else
        {
            _reachedCheckpoint = false;
        }
        m_gameObject->UpdateColliders();
        SetIsUsable(false);
    }
    _tmpMovementVector = glm::vec3(0.0f);
}

void Platform::ActionStart()
{
    _start = true;
    if (_returnsOnDeactivation)
    {
        _direction = 1;
        _timer = 0;
    }
}

void Platform::AddTravelVector(glm::vec4 vector)
{
    _travelVectors.push_back(vector);
    _tmpVec = glm::vec4(0.0f);
}

void Platform::ReplaceTravelVector(glm::vec4 vector, int id)
{
    _travelVectors[id] = vector;
}

void Platform::RemoveTravelVector(int i)
{
    if (i < _travelVectors.size())
    {
        _travelVectors.erase(_travelVectors.begin() + i);
        _tmpId = 0;
    }
}

void Platform::SetRepetable(bool state)
{
    _repetable = state;
}

void Platform::SetReturnOnDeactivation(bool state)
{
    _returnsOnDeactivation = state;
}

void Platform::Reset()
{
    _tmpMovementVector = glm::vec3(0.0f);
    m_gameObject->m_transform->SetPosition(_travelPoints[0]);
    _actualLocation = 0;
    _direction = 1;
    _timer = 0.0f;
}

void Platform::GenerateTravelPoints()
{
    _travelPoints.clear();

    for (auto& vector : _travelVectors)
    {
        _travelPoints.push_back(glm::vec4(m_gameObject->m_transform->GetPosition(), 0) + vector);
    }
}

glm::vec3 Platform::GetTmpMovementVector()
{
    return _tmpMovementVector;
}

void Platform::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
    bool enabledTMP = enabled;
    ImGui::Text(" ");
    ImGui::Checkbox("=== [ Platform ] ===", &enabledTMP);
    ImGui::Checkbox("IsUsable", &_isUsable);
    ImGui::Checkbox("IsActive", &_isActive);
    ImGui::Checkbox("Repeatable", &_repetable);
    ImGui::Checkbox("Loop", &_loop);
    ImGui::Checkbox("Returns", &_returnsOnDeactivation);

    int i = 0;
    char tmpName[32];
    for (glm::vec4 vector : _travelVectors)
    {
        char finalName[64] = "TravelVec";
        std::sprintf(tmpName, "%d", i);
        std::strcat(finalName, tmpName);
        ImGui::InputFloat4(finalName, (float*)&vector, "%.3f");
        i++;
    }

    if (ImGui::Button("Refresh Platform"))
    {
        GenerateTravelPoints();
        Reset();
    }

    ImGui::Text(" ");
    ImGui::InputFloat4("NewVec", (float*)&_tmpVec, "%.3f");
    ImGui::InputInt("Operation ID", (int*)&_tmpId);
    if (ImGui::Button("Add NewVec"))
    {
        if (_tmpId > _travelVectors.size() - 1)
            AddTravelVector(_tmpVec);
        else
            ReplaceTravelVector(_tmpVec, _tmpId);
        Start();
    }
    if (ImGui::Button("Remove Vec"))
    {
        RemoveTravelVector(_tmpId);
        Start();
    }

    if (ImGui::Button("Go to origin"))
    {
        m_gameObject->m_transform->SetPosition(_travelPoints[0]);
    }
    
    this->SetEnabled(enabledTMP);
}

bool Platform::CloseVectors(glm::vec3 a, glm::vec3 b, float lenght)
{
    if ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z) <= lenght * lenght)
        return true;
    return false;
}

glm::vec3 Platform::Lerp(glm::vec3 a, glm::vec3 b, float t)
{
    if (t > 1.0f) t = 1.0f;
    glm::vec3 final = a * (1.f - t) + b * t;
    _tmpMovementVector = final - m_gameObject->m_transform->GetPosition();
    return final;
}
