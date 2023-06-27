import torch

from snob_base import Permutation
from snob_base import IntegerPartition
from snob_base import IntegerPartitions
from snob_base import YoungTableau
from snob_base import StandardYoungTableaux

from snob_base import SnElement
from snob_base import SnCClass
from snob_base import SnCharacter
from snob_base import SnIrrep
from snob_base import Sn
from snob_base import SnType

def device_id(device):
    if device==0:
        return 0
    if device==1:
        return 1
    if device=='cpu':
        return 0
    if device=='gpu':
        return 1
    if device=='cuda':
        return 1
    if device=='cuda:0':
        return 1
    return 0

from snob.SnFunction import *

