#pragma once
#include "util/vectors.hpp"
#include "event.hpp"
#include <inttypes.h>
#include <memory>
namespace GameFr{
	class Camera2D;
	class Entity2D : public std::enable_shared_from_this<Entity2D>{
	public:
		Vector2 position;
		uint32_t width, height;
		void Push(const Vector2& direction, const float& speed);			   //Push an object in a desired direction
		bool CollidingRect(const Entity2D& other) const;				   //Simple AABB collision detection
		bool CollidingCircle(const Entity2D& other, const uint32_t desiredDistance) const; //Check if this is in a certain range of another Entity2D object
		virtual void Update() = 0;

		std::shared_ptr<const Entity2D> GetPtr() const;
		Entity2D();

	protected:
		/*
		 *	Make sure to put this in an update function so that the renderer knows where to draw the object
		 *	Call it with the arguments of the rect that your rendering library is using
		 *	And the template argument that represents the type that the rect uses
		 *	Ex: 
		 *		Raylib: 
		 *		AssignDimensionsToRenderingLibRect<float>(rect.x, rect.y, rect.w, rect.h);
		 */
		template<typename T>
		void AssignDimensionsToRenderingLibRect(T& X, T& Y, T& W, T& H){
			X = renderingPosition.X;
			Y = renderingPosition.Y;
			W = width;
			H = height;
		}
		/*
		 *	Use the following three in an update function
		 *	Their purpose is to check if this entity is visible on camera
		 */
		Vector2 renderingPosition;				//The position that reflects where on screen this entity is located
		bool onScreen;						//Is assigned in GetRenderingPosition(), use to chek if this is on screen in Update()
		void GetRenderingPosition(const Camera2D& camera);	/* Gets the position that reflects where this should be rendered
									 * and also checks if it's visible on the given camera
									*/
		EventInterface eventInterface;
	};

	class Entity3D{
		Vector3 position;
	};
}
