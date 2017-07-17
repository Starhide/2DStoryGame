boomerang = {
	Graphics = {
        anim:SetBank("boomerang"),
        anim:SetBuild("boomerang"),
        anim:PlayAnimation("idle"),
        anim:SetRayTestOnBB(true)
    },

    Tags = {
        "projectile",
        "thrown"
    },   

    Weapon = {
        damage = (TUNING.BOOMERANG_DAMAGE),
        range = {TUNING.BOOMERANG_DISTANCE, TUNING.BOOMERANG_DISTANCE+2}
    },

    FiniteUses = {
        MaxUses = TUNING.BOOMERANG_USES,
        Uses = TUNING.BOOMERANG_USES,    
        OnFinished = function (inst)
            inst.AnimState:PlayAnimation("used")
            inst:ListenForEvent("animover", function() inst:Remove() end)
        end
    },

    Inspectable = {

    },
    
    Projectile = {
        Speed = 10,
        CanCatch = true,
        OnThrownFn = function (inst, owner, target)
            if target ~= owner then
                owner.SoundEmitter:PlaySound("dontstarve/wilson/boomerang_throw")
            end
            inst.AnimState:PlayAnimation("spin_loop", true)
        end,

        OnHitFn = function (inst, owner, target)
            if owner == target then
                OnDropped(inst)
            else
                ReturnToOwner(inst, owner)
            end
            local impactfx = SpawnPrefab("impact")
            if impactfx then
        	    local follower = impactfx.entity:AddFollower()
        	    follower:FollowSymbol(target.GUID, target.components.combat.hiteffectsymbol, 0, 0, 0 )
                impactfx:FacePoint(inst.Transform:GetWorldPosition())
            end
        end,

        OnMissFn = function (inst, owner)
            if owner and not (inst.components.finiteuses and inst.components.finiteuses:GetUses() < 1) then
                owner.SoundEmitter:PlaySound("dontstarve/wilson/boomerang_return")
                inst.components.projectile:Throw(owner, owner)
            end
        end,

        OnCaughtFn = function (inst, catcher)
            if catcher then
                if catcher.components.inventory then
                    if inst.components.equippable and not catcher.components.inventory:GetEquippedItem(inst.components.equippable.equipslot) then
        				catcher.components.inventory:Equip(inst)
        			else
                        catcher.components.inventory:GiveItem(inst)
                    end
                    catcher:PushEvent("catch")
                end
            end
        end
    },
    
    InventoryItem = {
        OnDroppedFn = function (inst)
            inst.AnimState:PlayAnimation("idle")
        end
    },
    
    Equippable = {
        OnEquip = function (inst, owner) 
            owner.AnimState:OverrideSymbol("swap_object", "swap_boomerang", "swap_boomerang")
            owner.AnimState:Show("ARM_carry") 
            owner.AnimState:Hide("ARM_normal") 
        end,

        OnUnequip = function (inst, owner) 
            owner.AnimState:Hide("ARM_carry") 
            owner.AnimState:Show("ARM_normal") 
        end
    }
}

return boomerang