#define verifyIDSafe(Member_, ID_) \
    if(Member_ && Member_->getID() != ID_) { \
        log::warn("{} has an invalid ID - {} (expected {})", #Member_, Member_->getID(), ID_); \
    }

#define verifyParentIDSafe(Member_, ID_) \
    if(Member_ && Member_->getParent() && Member_->getParent()->getID() != ID_) { \
        log::warn("{}'s parent has an invalid ID - {} (expected {})", #Member_, m_rightArrow->getParent()->getID(), ID_); \
    }