#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include "../Mathobj/mathobjs.h"
#include "../Mathobj/pixel.h"
#include "../objects/point.h"
#include "AbstractFactory/drawer.h"
#include "load/scenefileloader.h"
#include "managers/configmanager.h"
#include "managers/drawmanager.h"
#include "managers/loadmanager.h"
#include "managers/scenemanager.h"


class BaseCommand
{
public:
    BaseCommand() = default;
    ~BaseCommand() = default;

    virtual void execute() = 0;
};

class BaseCameraCommand : public BaseCommand
{
public:
    BaseCameraCommand() = default;
    ~BaseCameraCommand() = default;

    virtual void execute() = 0;
};

class BaseFigureCommand : public BaseCommand
{
public:
    BaseFigureCommand() = default;
    ~BaseFigureCommand() = default;

    virtual void execute() = 0;
};

class BaseSceneCommand : public BaseCommand
{
public:
    BaseSceneCommand() = default;
    ~BaseSceneCommand() = default;

    virtual void execute() = 0;
};

class BaseObjectCommand : public BaseCommand
{
public:
    BaseObjectCommand() = default;
    ~BaseObjectCommand() = default;

    virtual void execute() = 0;
};

class DrawScene : public BaseSceneCommand
{
public:
    DrawScene() = default;
    DrawScene(std::shared_ptr<BaseDrawer> _drawer) : drawer(_drawer) {};
    ~DrawScene() = default;

    virtual void execute() override;

private:
    std::shared_ptr<BaseDrawer> drawer;
};

class LoadScene : public BaseSceneCommand
{
public:
    LoadScene(const string &_file_name) : file_name(_file_name) {};
    ~LoadScene() = default;

    virtual void execute() override;

private:
    string file_name;
};

class LoadCamera : public BaseCameraCommand
{
public:
    LoadCamera(const string &_file_name) : file_name(_file_name) {};
    ~LoadCamera() = default;

    virtual void execute() override;

private:
    string file_name;
};

class SetCamera : public BaseCameraCommand
{
public:
    SetCamera(int _camera) : camera(_camera) {};
    ~SetCamera() = default;

    virtual void execute() override;

private:
    int camera;
};

class LoadFigure : public BaseFigureCommand
{
public:
    LoadFigure(const string &_file_name) : file_name(_file_name) {};
    ~LoadFigure() = default;

    virtual void execute() override;

private:
    string file_name;
};

class AddObject : public BaseObjectCommand
{
public:
    AddObject(const shared_ptr<Object> &_obj) : object(_obj) {};
    ~AddObject() = default;

    virtual void execute() override;

private:
    shared_ptr<Object> object;

};

class RemoveObject : public BaseObjectCommand
{
public:
    RemoveObject(int _index) : index(_index) {};
    ~RemoveObject() = default;

    virtual void execute() override;

private:
    int index;
};

class RotateObject : public BaseObjectCommand
{
public:
    RotateObject(int _index, const Angle &_rotate) : index(_index), rotate(_rotate)  {};
    ~RotateObject() = default;

    virtual void execute() override;

private:
    int index;
    Angle rotate;
};

class TransferObject : public BaseObjectCommand
{
public:
    TransferObject(int _index, const Point &_transfer) : index(_index), transfer(_transfer)  {};
    ~TransferObject() = default;

    virtual void execute() override;

private:
    int index;
    Point transfer;
};

class ScaleObject : public BaseObjectCommand
{
public:
    ScaleObject(int _index, const ScaleCoef &_scale) : index(_index), scale(_scale)  {};
    ~ScaleObject() = default;

    virtual void execute() override;

private:
    int index;
    ScaleCoef scale;
};

#endif // BASECOMMAND_H
