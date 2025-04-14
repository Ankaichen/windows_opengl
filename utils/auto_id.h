/**
  ******************************************************************************
  * @file           : auto_id.h
  * @author         : An Kaichen
  * @brief          : None
  * @attention      : None
  * @date           : 2025-04-14
  ******************************************************************************
  */

#ifndef OPENGL_AUTO_ID_H
#define OPENGL_AUTO_ID_H

template<typename Derived>
class AutoId {
public:
    AutoId() : mId{mClassId++} {}

    [[nodiscard]] inline unsigned int getId() const { return this->mId; }

private:
    const unsigned int mId;
    static unsigned int mClassId;
};

template<typename Derived>
unsigned int AutoId<Derived>::mClassId = 0;

#endif //OPENGL_AUTO_ID_H
