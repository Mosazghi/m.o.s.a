import { Injectable } from '@nestjs/common';
import { PassportSerializer } from '@nestjs/passport';
import { UserService } from 'src/user/user.service';

@Injectable()
export class SessionSerializer extends PassportSerializer {
  constructor(private userService: UserService) {
    super();
  }
  serializeUser(user: any, done: (err: Error, user: any) => void) {
    console.log('ser id: ', user._doc._id);
    console.log('logget som:', user._doc.username);
    done(null, user._doc._id);
  }
  deserializeUser(id: any, done: (err: Error, id: any) => void) {
    try {
      console.log('des id: ', id);
      const user = this.userService.findById(id);
      done(null, user);
    } catch (err) {
      done(null, err);
    }
  }
}
