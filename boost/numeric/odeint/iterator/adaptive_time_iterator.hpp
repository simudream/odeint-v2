
/*
 [auto_generated]
 boost/numeric/odeint/iterator/adaptive_time_iterator.hpp

 [begin_description]
 Iterator for iterating throught the solution of an ODE with adaptive step size. The dereferenced types containes also the time.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_ADAPTIVE_TIME_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_ADAPTIVE_TIME_ITERATOR_HPP_INCLUDED


#include <boost/numeric/odeint/util/unit_helper.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/iterator/detail/ode_time_iterator_base.hpp>


namespace boost {
namespace numeric {
namespace odeint {


    template< class Stepper , class System , class StepperTag = typename base_tag< typename Stepper::stepper_category >::type > 
    class adaptive_time_iterator;


    /*
     * Specilization for controlled steppers
     */
    /**
     * \brief ODE Iterator with adaptive step size control. The value type of this iterator is a pair of state type and time type of the stepper.
     *
     * Implements an ODE with adaptive step size control. Uses controlled steppers. adaptive_iterator is a model
     * of single-pass iterator.
     *
     * The value type of this iterator is a pair of state type and time type of the stepper.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     */
    template< class Stepper , class System >
    class adaptive_time_iterator< Stepper , System , controlled_stepper_tag > : public detail::ode_time_iterator_base
    <
        adaptive_time_iterator< Stepper , System , controlled_stepper_tag > ,
        Stepper , System , controlled_stepper_tag
    >
    {
    private:

        typedef Stepper stepper_type;
        typedef System system_type;
        typedef typename stepper_type::state_type state_type;
        typedef typename stepper_type::time_type time_type;
        typedef typename stepper_type::value_type ode_value_type;
        typedef detail::ode_time_iterator_base<
            adaptive_time_iterator< Stepper , System , controlled_stepper_tag > ,
            Stepper , System , controlled_stepper_tag > base_type;


    public:

        /**
         * \brief Constructs an adaptive_time_iterator. This constructor should be used to construct the begin iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. adaptive iterator store a reference of s and changes its value during the iteration.
         * \param t The initial time.
         * \param t_end The end time, at which the iteration should stop.
         * \param dt The initial time step.
         */
        adaptive_time_iterator( stepper_type stepper , system_type sys , state_type &s , time_type t , time_type t_end , time_type dt )
            : base_type( stepper , sys , s , t , t_end , dt ) {}

        /**
         * \brief Constructs an adaptive_time_iterator. This constructor should be used to construct the end iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. adaptive iterator store a reference of s and changes its value during the iteration.
         */
        adaptive_time_iterator( stepper_type stepper , system_type sys , state_type &s )
            : base_type( stepper , sys , s ) {}

    private:

        friend class boost::iterator_core_access;

        void increment()
        {
            const size_t max_attempts = 1000;
            size_t trials = 0;
            controlled_step_result res = success;
            do
            {
                res = this->m_stepper.try_step( this->m_system , this->m_state.first , this->m_state.second , this->m_dt );
                ++trials;
            }
            while( ( res == fail ) && ( trials < max_attempts ) );
            if( trials == max_attempts )
            {
                throw std::overflow_error( "Adaptive iterator : Maximal number of iterations reached. A step size could not be found." );
            }
            this->check_end();
        }
    };






    /*
     * Specilization for steppers and error steppers
     */
    /**
     * \brief ODE Iterator with adaptive step size control. The value type of this iterator is a pair of state type and time type of the stepper.
     *
     * Implements an ODE with adaptive step size control. Uses dense-output steppers. adaptive_iterator is a model
     * of single-pass iterator.
     *
     * The value type of this iterator is a pair of state type and time type of the stepper.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     */
    template< class Stepper , class System >
    class adaptive_time_iterator< Stepper , System , dense_output_stepper_tag > : public detail::ode_time_iterator_base
    <
        adaptive_time_iterator< Stepper , System , dense_output_stepper_tag > ,
        Stepper , System , dense_output_stepper_tag
    >
    {
    private:

        typedef Stepper stepper_type;
        typedef System system_type;
        typedef typename stepper_type::state_type state_type;
        typedef typename stepper_type::time_type time_type;
        typedef typename stepper_type::value_type ode_value_type;
        typedef detail::ode_time_iterator_base<
            adaptive_time_iterator< Stepper , System , dense_output_stepper_tag > ,
            Stepper , System , dense_output_stepper_tag > base_type;

    public:

        /**
         * \brief Constructs an adaptive_time_iterator. This constructor should be used to construct the begin iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. adaptive iterator store a reference of s and changes its value during the iteration.
         * \param t The initial time.
         * \param t_end The end time, at which the iteration should stop.
         * \param dt The initial time step.
         */
        adaptive_time_iterator( stepper_type stepper , system_type sys , state_type &s , time_type t , time_type t_end , time_type dt )
            : base_type( stepper , sys , s , t , t_end , dt ) 
        {
            this->m_stepper.initialize( this->m_state.first , this->m_state.second , this->m_dt );
        }

        /**
         * \brief Constructs an adaptive_time_iterator. This constructor should be used to construct the end iterator.
         *
         * \param stepper The stepper to use during the iteration.
         * \param sys The system function (ODE) to solve.
         * \param s The initial state. adaptive iterator store a reference of s and changes its value during the iteration.
         */
        adaptive_time_iterator( stepper_type stepper , system_type sys , state_type &s )
            : base_type( stepper , sys , s )
        {
        }


    private:

        friend class boost::iterator_core_access;

        void increment()
        {
            this->m_stepper.do_step( this->m_system );
            this->m_state.second = this->m_stepper.current_time();
            this->m_stepper.calc_state( this->m_state.second , this->m_state.first );
            this->check_end();
        }
    };








    template< class Stepper , class System >
    adaptive_time_iterator< Stepper , System > make_adaptive_time_iterator_begin(
        Stepper stepper ,
        System system , 
        typename Stepper::state_type &x ,
        typename Stepper::time_type t ,
        typename Stepper::time_type t_end ,
        typename Stepper::time_type dt )
    {
        return adaptive_time_iterator< Stepper , System >( stepper , system , x , t , t_end , dt );
    }

    template< class Stepper , class System >
    adaptive_time_iterator< Stepper , System > make_adaptive_time_iterator_end(
        Stepper stepper ,
        System system , 
        typename Stepper::state_type &x )
    {
        return adaptive_time_iterator< Stepper , System >( stepper , system , x );
    }


    template< class Stepper , class System >
    std::pair< adaptive_time_iterator< Stepper , System > , adaptive_time_iterator< Stepper , System > >
    make_adaptive_time_range(
        Stepper stepper ,
        System system , 
        typename Stepper::state_type &x ,
        typename Stepper::time_type t_start ,
        typename Stepper::time_type t_end ,
        typename Stepper::time_type dt )
    {
        return std::make_pair(
            adaptive_time_iterator< Stepper , System >( stepper , system , x , t_start , t_end , dt ) ,
            adaptive_time_iterator< Stepper , System >( stepper , system , x ) );
    }






    /**
     * \fn make_adaptive_time_iterator_begin( Stepper stepper , System system , typename Stepper::state_type &x , typename Stepper::time_type t , typename Stepper::time_type t_end , typename Stepper::time_type dt )
     *
     * \brief Factory function for adaptive_time_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. adaptive iterator store a reference of s and changes its value during the iteration.
     * \param t The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The adaptive time iterator.
     */


    /**
     * \fn make_adaptive_iterator_end( Stepper stepper , System system , typename Stepper::state_type &x )
     * \brief Factory function for adaptive_time_iterator. Constructs a end iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. adaptive iterator store a reference of s and changes its value during the iteration.
     * \returns The adaptive time iterator.
     */


    /**
     * \fn make_adaptive_range( Stepper stepper , System system , typename Stepper::state_type &x , typename Stepper::time_type t_start , typename Stepper::time_type t_end , typename Stepper::time_type dt )
     *
     * \brief Factory function to construct a single pass range of adaptive time iterators. A range is here a pair of adaptive_time_iterators.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. adaptive iterator store a reference of s and changes its value during the iteration.
     * \param t The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The adaptive time range.
     */










} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_ITERATOR_ADAPTIVE_TIME_ITERATOR_HPP_INCLUDED
