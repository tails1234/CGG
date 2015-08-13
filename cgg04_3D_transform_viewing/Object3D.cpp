#include "Object3D.h"
#include "Mathtools.h"


Object3D::Object3D() : texture_(0)
{
	material_ = new Material(this);
}


Object3D::Object3D(const Object3D& src)
{
}


Object3D::~Object3D()
{
	for (Vector3D *point : points_)
	{
		if (point)
			delete point;
	}

	for (Surface3D *tri : triangles_)
	{
		if (tri)
			delete tri;
	}
}


void Object3D::updateColor()
{
	for (Surface3D *tri : triangles_)
	{
		if (tri)
			tri->setColor(material_->getColor());
	}
}

Vector3D* Object3D::getPoint(int index)
{
	return points_[index];
}


Surface3D* Object3D::getTriangle(int index)
{
	return triangles_[index];
}


unsigned int Object3D::getPointSize()
{
	return points_.size();
}


unsigned int Object3D::getTriangleSize()
{
	return triangles_.size();
}


Material* Object3D::getMaterial()
{
	return material_;
}

std::vector<Surface3D*> Object3D::getTriangleList()
{
	return triangles_;
}


Texture* Object3D::getTexture()
{
	return texture_;
}


void Object3D::linkTexture(Texture* texture)
{
	// to be continued
	if (!texture)
		return;
}


void Object3D::rotate(const double rx, const double ry, const double rz)
{
	TransformMatrix3D x, y, z;
	x.rotateAroundX(rx);
	y.rotateAroundY(ry);
	z.rotateAroundZ(rz);

	TransformMatrix3D transform = x * y * z;
	this->transform(transform);
}

void Object3D::rotateX(const double rx)
{
	TransformMatrix3D transform;
	transform.rotateAroundX(rx);
	this->transform(transform);
}

void Object3D::rotateY(const double ry)
{
	TransformMatrix3D transform;
	transform.rotateAroundY(ry);
	this->transform(transform);
}

void Object3D::rotateZ(const double rz)
{
	TransformMatrix3D transform;
	transform.rotateAroundZ(rz);
	this->transform(transform);
}

void Object3D::translate(const double tx, const double ty, const double tz)
{
	TransformMatrix3D transform;
	transform.translate(tx, ty, tz);
	this->transform(transform);
}

void Object3D::scale(const double sx, const double sy, const double sz)
{
	TransformMatrix3D transform;
	transform.scale(sx, sy, sz);
	this->transform(transform);
}


void Object3D::transform(TransformMatrix3D& matrix)
{
	for (Vector3D* point : points_)
	{
		point->setVector(matrix * (*point));
	}
}