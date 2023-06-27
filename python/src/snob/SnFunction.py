
# This file is part of Snob2, a symmetric group FFT library. 
# 
# Copyright (c) 2021, Imre Risi Kondor
#
# This Source Code Form is subject to the terms of the Mozilla
# Public License v. 2.0. If a copy of the MPL was not distributed
# with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

import torch
from snob_base import SnFunction as _SnFunction

from snob import device_id


class SnFunction(torch.Tensor):

    @classmethod
    def dummy(self):
        R=SnFunction(1)
        return R

    @classmethod
    def zeros(self,n,device='cpu'):
        R=SnFunction(1)
        R.obj=_SnFunction.zero(n,device_id(device))
        return R

    @classmethod
    def ones(self,n,device='cpu'):
        R=SnFunction(1)
        R.obj=_SnFunction.ones(n,device_id(device))
        return R

    @classmethod
    def gaussian(self,n,device='cpu'):
        R=SnFunction(1)
        R.obj=_SnFunction.gaussian(n,device_id(device))
        return R

    @classmethod
    def sequential(self,n,device='cpu'):
        R=SnFunction(1)
        R.obj=_SnFunction.sequential(n,device_id(device))
        return R


    # ---- Access ------------------------------------------------------------------------------------------


    def get_dev(self):
        return self.obj.device()

    #def getb(self):
    #    return self.obj.getb()

    def getn(self):
        return self.obj.getn()


    def get_grad(self):
        R=SO3vecC(1)
        R.obj=self.obj.get_grad()
        return R

    def torch(self):
        return SO3vecC_toTorchFn.apply(self)


    # ---- Operations ---------------------------------------------------------------------------------------


    def left_translate(self,tau):
        return LeftTranslateFn.apply(self,tau)

    def right_translate(self,tau):
        return RightTranslateFn.apply(self,tau)

    def inv(self):
        return InvFn.apply(self)

    def convolve(self,tau):
        return ConvolveFn.apply(self,tau)


    # ---- I/O ----------------------------------------------------------------------------------------------


    def __repr__(self):
        return self.obj.__repr__()

    def __str__(self):
        return self.obj.__str__()


# ----------------------------------------------------------------------------------------------------------
# ---- Autograd functions -----------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------


class LeftTranslateFn(torch.autograd.Function):

    @staticmethod
    def forward(ctx,x,tau):
        r=SnFunction(0)
        r.obj=x.obj.left_translate(tau)
        ctx.x=x
        ctx.r=r
        ctx.tau=tau
        return r

    @staticmethod
    def backward(ctx,g):
        ctx.x.obj.set_grad(g.left_translate(tau.inv()))
        return SnFunction.dummy(), None


class RightTranslateFn(torch.autograd.Function):

    @staticmethod
    def forward(ctx,x,tau):
        r=SnFunction(0)
        r.obj=x.obj.right_translate(tau)
        ctx.x=x
        ctx.r=r
        ctx.tau=tau
        return r

    @staticmethod
    def backward(ctx,g):
        ctx.x.obj.set_grad(g.right_translate(tau.inv()))
        return SnFunction.dummy(), None


class InvFn(torch.autograd.Function):

    @staticmethod
    def forward(ctx,x):
        r=SnFunction(0)
        r.obj=x.obj.inv()
        ctx.x=x
        ctx.r=r
        return r

    @staticmethod
    def backward(ctx,g):
        ctx.x.obj.set_grad(g.inv())
        return SnFunction.dummy()


class ConvolveFn(torch.autograd.Function):

    @staticmethod
    def forward(ctx,x,y):
        r=SnFunction(0)
        r.obj=x.obj.convolve(y)
        ctx.x=x
        ctx.y=y
        ctx.r=r
        return r

    # TODO
    @staticmethod
    def backward(ctx,g):
        ctx.x.obj.set_grad(g.convolve(y))
        ctx.y.obj.set_grad(g.convolve(x))
        return SnFunction.dummy(), SnFunction.dummy()


