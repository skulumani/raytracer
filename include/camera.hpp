#ifndef CAMERA_H
#define CAMERA_H


#include <Eigen/Dense>

class Camera {
    private:
        Eigen::Vector3f m_position;

        Eigen::Vector3f m_view_axis;
        Eigen::Vector3f m_up_axis;
        Eigen::Vector3f m_right_axis;

        Eigen::Vector2f m_fov;
        Eigen::Vector2i m_center;

        float fov_h, fov_w;
    
        // image plane size in pixels
        float width, height;

        float plane_dist;
        
        void init();
    public:
        Camera( void );
        virtual ~Camera( void ) {};
        
        inline Camera& position(const Eigen::Ref<const Eigen::Vector3f>& pos_in) {
            m_position = pos_in;
            return *this;
        }

        inline Camera& view_axis(const Eigen::Ref<const Eigen::Vector3f> &view_axis_in) {
            m_view_axis = view_axis_in;
            return *this;
        }
       
        inline Camera& up_axis(const Eigen::Ref<const Eigen::Vector3f>& up_axis_in) {
            m_up_axis = up_axis_in;
            return *this;
        }

        inline Camera& right_axis(const Eigen::Ref<const Eigen::Vector3f>& right_axis_in) {
            m_right_axis = right_axis_in;
            return *this;
        }

        
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

        // TODO Rotate cam
        // TODO translate cam
};


#endif
