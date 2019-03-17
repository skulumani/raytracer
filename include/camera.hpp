#ifndef CAMERA_H
#define CAMERA_H


#include <Eigen/Dense>

class Camera {
    private:
        Eigen::Vector3f m_position;

        Eigen::Vector3f m_view_axis;
        Eigen::Vector3f m_up_axis;
        Eigen::Vector3f m_right_axis;
        
        // TODO Need to be consistent
        Eigen::Vector2f m_focal;
        // image plane size in pixels width, height
        Eigen::Vector2i m_image_size;

        Eigen::Vector2i m_center;

        Eigen::Matrix<float, 3, 4> extrinsic;
        Eigen::Matrix3f intrinsic;
        
        void init( void );

    public:
        Camera( void );
        virtual ~Camera( void ) {};
        
        inline Camera& position(const Eigen::Ref<const Eigen::Vector3f>& pos_in) {
            m_position = pos_in;
            init();
            return *this;
        }

        inline Camera& view_axis(const Eigen::Ref<const Eigen::Vector3f> &view_axis_in) {
            m_view_axis = view_axis_in;
            init();
            return *this;
        }
       
        inline Camera& up_axis(const Eigen::Ref<const Eigen::Vector3f>& up_axis_in) {
            m_up_axis = up_axis_in;
            init();
            return *this;
        }

        inline Camera& right_axis(const Eigen::Ref<const Eigen::Vector3f>& right_axis_in) {
            m_right_axis = right_axis_in;
            init();
            return *this;
        }
        
        inline Camera& focal(const Eigen::Ref<const Eigen::Vector2f>& focal_in) {
            m_focal = focal_in;
            init();
            return *this;
        }

        inline Camera& center(const Eigen::Ref<const Eigen::Vector2i>& center_in) {
            m_center = center_in;
            init();
            return *this;
        }

        inline Camera& image_size(const Eigen::Ref<const Eigen::Vector2i>& image_size_in) {
            m_image_size = image_size_in;
            init();
            return *this;
        }

        Eigen::Vector3f get_position( void ) const;
        /** @fn EigeN::Vector3f get_ray(const int& px, const int& py) const
                
            Get the ray from camera center to center of pixel px, py in the 
            inertial frame

            @param px Pixel x 
            @param py Pixel y
            @returns ray Vector

            @author Shankar Kulumani
            @version 16 March 2019
        */
        Eigen::Vector3f get_ray(const int& px, const int& py) const;
        Eigen::Vector3f get_ray(const float& px, const float& py) const;
        Eigen::Vector3f get_ray(const Eigen::Ref<const Eigen::Vector2f>& p_in) const;

        // get the pixel coordinate for a ray from camera
        Eigen::Vector2f get_pixel(const Eigen::Ref<const Eigen::Vector3f>& ray) const;

        // TODO Rotate cam
        // TODO translate cam
        // TODO put inside the renderer
        // TODO Cast ray to scene
        // TODO Return an image for every pixel
};


#endif
