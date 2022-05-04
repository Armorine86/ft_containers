/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:04:10 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/04 13:43:08 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prelude.hpp"

void stack_test_misc()
{
    {
        ft::stack<int, ft::vector<int, leak_allocator<int> > > st;

        PRINT_LINE("Empty:", (st.empty() ? "true" : "false"));

        st.push(34);

        PRINT_LINE("Size:", st.size());
        PRINT_LINE("Empty:", (st.empty() ? "true" : "false"));
        PRINT_LINE("Top:", st.top());

        st.push(64);

        PRINT_LINE("Size:", st.size());
        PRINT_LINE("Empty:", (st.empty() ? "true" : "false"));
        PRINT_LINE("Top:", st.top());

        st.top() = 1;

        PRINT_LINE("Size:", st.size());
        PRINT_LINE("Empty:", (st.empty() ? "true" : "false"));
        PRINT_LINE("Top:", st.top());

        st.push(128);

        PRINT_LINE("Size:", st.size());
        PRINT_LINE("Top:", st.top());

        const ft::stack<int, ft::vector<int, leak_allocator<int> > > st1(st);

        PRINT_LINE("Size:", st.size());
        PRINT_LINE("Empty:", (st.empty() ? "true" : "false"));
        PRINT_LINE("Top:", st.top());

        st.pop();
        st.pop();

        PRINT_LINE("Size:", st.size());
        PRINT_LINE("Empty:", (st.empty() ? "true" : "false"));
        PRINT_LINE("Top:", st.top());

        st.pop();

        PRINT_LINE("Size:", st.size());
        PRINT_LINE("Empty:", (st.empty() ? "true" : "false"));
        PRINT_LINE("Top:", st.top());

        st = st1;

        PRINT_LINE("Size:", st.size());
        PRINT_LINE("Empty:", (st.empty() ? "true" : "false"));
        PRINT_LINE("Top:", st.top());
    }
}

#ifndef SINGLE_BINARY
int main()
{
    stack_test_misc();
    CHECK_LEAKS(int);
    CHECK_DTOR(int);
    CHECK_DTOR(long);
}
#endif
