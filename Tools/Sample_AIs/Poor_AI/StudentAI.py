
]�]�  �               @   s{   d  d l  Z  d  d l m Z d  d l m Z d  d l m Z d  d l m Z d d �  Z d d	 �  Z	 Gd
 d �  d � Z
 d S)�    N)�defaultdict)�randint)�Move)�Boardc       	      C   s�   d } |  j  | � } x| | D]t } xk | D]c } | d } | d } t t | d | d � t | d | d � � } | d k r) | | 7} q) Wq W| S)Nr   �   )�get_all_possible_moves�max�abs)	ZOO0OO0000O0O0OO0OZO0O000000000OO00OZOO0O0O00000000O0OZOOO0O0OOOO000O000ZOO0OO00O0OO000000ZOOO0OO00OOO0O0OO0ZO00000000OOOOO00OZO000OO00O0OOO0O0OZOOO0O0O00O0OOOOO0� r
   �e/Users/zhangziyang/199project/Checkers_Teacher/Checkers_Student/Tools/Sample_AIs/Poor_AI/StudentAI.py�FUNC_A   s    

3r   c       
      C   s�   g  } t  t � } |  j | � } xz | D]r } xi | D]a } t j |  � } | j | | � t | | � }	 |	 d k r� | |	 j | � q5 | j | � q5 Wq( W| g  k r� | t | j	 �  � d S| S)Nr   )
r   �listr   �copy�deepcopy�	make_mover   �append�sorted�keys)
ZOO0OO0O0OO0OO0O00ZO0000OO0O0OOOOOOOZO0O00000OOO00OO00ZOO0OOO00OO0O0000OZO00000O0OO00O0OO0ZOOO00OOO000O0000OZOO0O0OO000O0O0000ZOOO0000OO0O0O0OO0ZOOOOO00OO0OOO00O0ZOO00OO00000O0O00Or
   r
   r   �FUNC_B   s    r   c               @   s(   e  Z d  Z d d �  Z d d �  Z d S)�	StudentAIc             C   sh   | |  _  | |  _ | |  _ t | | | � |  _ |  j j �  d |  _ d d d d i |  _ d |  _ d  S)N� r   �   )�col�row�pr   �board�initialize_game�color�opponent)ZOO0OOO0OOOOO00000ZOO00OO0OO0O0O0O00ZO0OO0000000O0O00OZO0OO0O0O00000OO0Or
   r
   r   �__init__"   s    				zStudentAI.__init__c             C   s�  t  | � d k r2 |  j j | |  j |  j � n	 d |  _ |  j j |  j � } | } d } d } x� | D]� } x� | D]� } t  | � | k rv t  | � | k r� t  | � } | } d } qv | d k rv | d } | d } t | d | d � t | d | d � d k rv | } d } qv Wqi W| rnt |  j |  j |  j |  j � }	 t d t  |	 � d � }
 |	 |
 } |  j j | |  j � | S)Nr   r   r   TF)	�lenr   r   r   r   r   r	   r   r   )ZO0OO0OO00O0O0OOO0ZOOO0OOO0OO00OO0OOZOOO0O000OOO00O00OZOOOO00OO0O0OO0000ZOO00O0OOO00OOO0OOZO0OO0O00OO0OO000OZOO00OO00OOO000O00ZOO00O0O00O0OOOO00ZOO00OO00OO000O0O0ZO0O0O00OOOO0OOOO0ZO000OO0OO00O0OO00r
   r
   r   �get_move+   s4     		

4"
zStudentAI.get_moveN)�__name__�
__module__�__qualname__r   r!   r
   r
   r
   r   r   !   s   	r   )r   �collectionsr   Zrandomr   �BoardClassesr   r   r   r   r   r
   r
   r
   r   �<module>   s   