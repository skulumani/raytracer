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
        // field of view (horiztonal and vertical)
        const Eigen::Vector2f m_fov = (Eigen::Vector2f() << M_PI/2.0, M_PI/2.0).finished(); 

        Eigen::Vector2i m_center;

        Eigen::Matrix<float, 3, 4> m_extrinsic;
        Eigen::Matrix3f m_intrinsic;
        
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
            // compute the image size
            m_image_size(0) = m_focal(0) * 2.0 * std::tan(m_fov(0) / 2.0);
            m_image_size(1) = m_focal(1) * 2.0 * std::tan(m_fov(1) / 2.0);
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
            // adjust the focal length
            m_focal(0) = m_image_size(0) / (2.0 * std::tan(m_fov(0) / 2.0));
            m_focal(1) = m_image_size(1) / (2.0 * std::tan(m_fov(1) / 2.0));
            m_center << image_size_in / 2;
            init();
            return *this;
        }

        inline Camera& image_size(const int& width, const int& height) {
            m_image_size << width, height;
            m_focal(0) = m_image_size(0) / (2.0 * std::tan(m_fov(0) / 2.0));
            m_focal(1) = m_image_size(1) / (2.0 * std::tan(m_fov(1) / 2.0));
            m_center << width / 2, height / 2;
            init();
            return *this;
        }

        Eigen::Vector3f get_position( void ) const;
        Eigen::Vector3f get_view_axis( void ) const;
        Eigen::Vector3f get_up_axis( void ) const;
        Eigen::Vector3f get_right_axis( void ) const;
        Eigen::Vector2f get_focal( void ) const;
        Eigen::Vector2i get_image_size( void ) const;
        Eigen::Vector2i get_center( void ) const;
        Eigen::Matrix<float, 3, 4> get_extrinsic( void ) const;
        Eigen::Matrix3f get_intrinsic( void ) const;
        /** @fn EigeN::Vector3f get_ray(const int& px, const int& py) const
                
            Get the ray from camera center to center of pixel px, py in the 
            inertial frame

            @param px Pixel x 
            @param py Pixel y
            @returns ray Vector

            @author Shankar Kulumani
            @version 16 March 2019
        */
        int get_ray(const float& px, const float& py,
                Eigen::Ref<Eigen::Vector3f> ray) const;
        int get_ray(const Eigen::Ref<const Eigen::Vector2f>& p_in,
                Eigen::Ref<Eigen::Vector3f> ray) const;

        // get the pixel coordinate for a ray from camera (position vector in camera frame)
        int get_pixel(const Eigen::Ref<const Eigen::Vector3f>& ray,
                Eigen::Ref<Eigen::Vector2f> pixel) const;
        int get_pixel(const float& rx, const float& ry, const float& rz,
                Eigen::Ref<Eigen::Vector2f> pixel) const;
        // TODO Think about templates for int/float/double types 
        
        // TODO Vector in the inertial frame (need to first get relative vector)
        // TODO Rotate cam
        // TODO translate cam
        // TODO put inside the renderer
        // TODO Cast ray to scene
        // TODO Return an image for every pixel
};


#endif
